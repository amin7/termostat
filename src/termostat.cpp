#include "termostat.h"
#include "settings_sub.h"
using namespace std;

const char *update_path = "/firmware";
bool is_safe_mode = false;
constexpr auto DEF_AP_PWD = "12345678";

Timezone myTZ((TimeChangeRule ) { "DST", Last, Sun, Mar, 3, +3 * 60 },
        (TimeChangeRule ) { "STD", Last, Sun, Oct, 4, +2 * 60 });

NTPtime ntpTime;

HomieDevice homie;

const char *pDeviceName = nullptr;

class CTimeKeeper: public SignalLoop<time_t> {
    bool getValue(time_t &val) {
        if (timeStatus() == timeNotSet) {
            return false;
        }
        val = myTZ.toLocal(now());
        return true;
    }
} timeKeeper;

DHTesp dht;
ADC_MODE(ADC_TOUT);
ESP8266WebServer serverWeb(SERVER_PORT_WEB);
ESP8266HTTPUpdateServer otaUpdater;
CWifiStateSignal wifiStateSignal;

CADC_filter ADC_filter(TermistorPin);

te_ret get_about(ostream &out) {
    out << "{";
    out << "\"firmware\":\"" << DEVICE_NAME << __DATE__ << " " << __TIME__ << "\"";
    out << ",\"deviceName\":\"" << pDeviceName << "\"";
    out << ",\"resetInfo\":" << system_get_rst_info()->reason;
    out << "}";
    return er_ok;
}

te_ret get_status(ostream &out) {
    const auto local = timeKeeper.getPreValue();
    out << "{\"timeStatus\":" << timeStatus();
    out << ",\"time\":\"";
    toTime(out, local);
    out << " ";
    toDate(out, local);
    out << "\"";
    out << ",\"temperature\":";
    toJson(out, dht.getTemperature());
    out << ",\"humidity\":";
    toJson(out, dht.getHumidity());
    out << ",\"mode\":" << "\"notset\"";
    out << ",\"mqtt\":" << homie.IsConnected();
    out << "}";
    return er_ok;
}

void setup_WebPages() {
    DBG_FUNK();
    otaUpdater.setup(&serverWeb, update_path, config.getCSTR("OTA_USERNAME"), config.getCSTR("OTA_PASSWORD"));

    serverWeb.on("/restart", []() {
        webRetResult(serverWeb, er_ok);
        delay(1000);
        ESP.restart();
    });

    serverWeb.on("/about", [] {
        wifiHandle_send_content_json(serverWeb, get_about);
    });

    serverWeb.on("/status", [] {
        wifiHandle_send_content_json(serverWeb, get_status);
    });

    serverWeb.on("/filesave", []() {
        DBG_FUNK();
        if (!serverWeb.hasArg("path") || !serverWeb.hasArg("payload")) {
            webRetResult(serverWeb, er_no_parameters);
            return;
        }
        const auto path = string("/www/") + serverWeb.arg("path").c_str();
        cout << path << endl;
        auto file = LittleFS.open(path.c_str(), "w");
        if (!file) {
            webRetResult(serverWeb, er_createFile);
            return;
        }
        if (!file.print(serverWeb.arg("payload"))) {
            webRetResult(serverWeb, er_FileIO);
            return;
        }
        file.close();
        webRetResult(serverWeb, er_ok);
    });

    serverWeb.on("/scanwifi", HTTP_ANY,
            [&]() {
                wifiHandle_sendlist(serverWeb);
            });
    serverWeb.on("/connectwifi", HTTP_ANY,
            [&]() {
                wifiHandle_connect(serverWeb);
            });
    serverWeb.on("/command", [&]() {
        if (!serverWeb.hasArg("handler")) {
            webRetResult(serverWeb, er_no_parameters);
            return;
        }
        const auto handler = serverWeb.arg("handler").c_str();
        int val = 0;
        if (serverWeb.hasArg("val")) {
            val = serverWeb.arg("val").toInt();
        }
        //  webRetResult(serverWeb, ledCmdSignal.onCmd(handler, val) ? er_ok : er_errorResult);
    });

    serverWeb.on("/getlogs", HTTP_ANY,
            [&]() {
                serverWeb.send(200, "text/plain", log_buffer.c_str());
                log_buffer = "";
            });

    serverWeb.on("/set_time", [&]() {
        DBG_FUNK();
        //todo
    });

    serverWeb.serveStatic("/", LittleFS, "/www/");

    serverWeb.onNotFound([] {
        Serial.println("Error no handler");
        Serial.println(serverWeb.uri());
        webRetResult(serverWeb, er_fileNotFound);
    });
    serverWeb.begin();
}

void setup_WIFIConnect() {
    DBG_FUNK();
    WiFi.begin();
    wifiStateSignal.onChange([](const wl_status_t &status) {
        wifi_status(cout);
    }
    );
    if (is_safe_mode) {
        WiFi.persistent(false);
        WiFi.mode(WIFI_AP);
        WiFi.softAP(pDeviceName, DEF_AP_PWD);
        DBG_OUT << "safemode AP " << pDeviceName << ",pwd: " << DEF_AP_PWD << ",ip:" << WiFi.softAPIP().toString() << std::endl;
    } else if (WIFI_STA == WiFi.getMode()) {
        DBG_OUT << "connecting <" << WiFi.SSID() << "> " << endl;
    }
}

void setup_signals() {
    DBG_FUNK();
//    ledCmdSignal.onSignal([&](const uint16_t val) {
//        mqtt_send();
//    });

    timeKeeper.onSignal([](const time_t &time) {
//todo schedule
    });
}

// We'll need a place to save pointers to our created properties so that we can access them again later.
HomieProperty *pTemperatureAir = NULL;
HomieProperty *pHumidity = NULL;
HomieProperty *pTemperatureFloor = NULL;
HomieProperty *pTemperatureFloorDesired = NULL;

void setup_homie() {
    DBG_FUNK();
    homie.strFriendlyName = pDeviceName;
    homie.strID = pDeviceName;
    homie.strID.toLowerCase();

    homie.strMqttServerIP = config.getCSTR("MQTT_SERVER");
    homie.MqttServerPort = config.getInt("MQTT_PORT");
    homie.strMqttUserName = "";
    homie.strMqttPassword = "";

    HomieLibRegisterDebugPrintCallback([](const char *szText) {
        DBG_OUT << szText << std::endl;
    });

    HomieNode *pNode = homie.NewNode();

    pNode->strID = "properties";
    pNode->strFriendlyName = "Properties";

    pTemperatureAir = pNode->NewProperty();
    pTemperatureAir->strFriendlyName = "Temperature Air";
    pTemperatureAir->strID = "temperature_air";
    pTemperatureAir->datatype = homieFloat;
    pTemperatureAir->SetUnit("°C");
    pTemperatureAir->SetRetained(true);
    pTemperatureAir->SetSettable(false);

    pHumidity = pNode->NewProperty();
    pHumidity->strFriendlyName = "Humidity Air";
    pHumidity->strID = "humidity_air";
    pHumidity->datatype = homieFloat;
    pHumidity->SetUnit("%");
    pHumidity->SetRetained(true);
    pHumidity->SetSettable(false);

    pTemperatureFloor = pNode->NewProperty();
    pTemperatureFloor->strFriendlyName = "Temperature Floor";
    pTemperatureFloor->strID = "temperature_flor";
    pTemperatureFloor->datatype = homieFloat;
    pTemperatureFloor->SetUnit("°C");
    pTemperatureFloor->SetRetained(true);
    pTemperatureFloor->SetSettable(false);

    pTemperatureFloorDesired = pNode->NewProperty();
    pTemperatureFloorDesired->strFriendlyName = "Temperature Desired";
    pTemperatureFloorDesired->strID = "temperature_flor_desired";
    pTemperatureFloorDesired->datatype = homieFloat;
    pTemperatureFloorDesired->SetUnit("°C");
    pTemperatureFloorDesired->SetRetained(true);
    pTemperatureFloorDesired->SetSettable(true);
    pTemperatureFloorDesired->SetValue("18.3");
    pTemperatureFloorDesired->strFormat = "10:40";

    pTemperatureFloorDesired->AddCallback([](HomieProperty *pSource) {
        //this property is settable. We'll print it into the console whenever it's updated.
        //you can set it from MQTT Explorer by publishing a number between 0-100 to homie/examplehomiedev/nodeid1/dimmer
        //but remember to check the *retain* box.
        DBG_OUT << pSource->strFriendlyName.c_str() << "%is now " << pSource->GetValue().c_str() << std::endl;
    });

    homie.Init();
}

void setup_config() {
    settings_config("/www/config/config.json");
    pDeviceName = config.getCSTR("DEVICE_NAME");
    settings_termostat("/www/config/termostat.json");
    settings_weekday("/www/config/weekday.json");
}

void setup() {
    is_safe_mode = false; //isSafeMode(GPIO_PIN_WALL_SWITCH, 3000);

    Serial.begin(SERIAL_BAUND);
    logs_begin();
    DBG_FUNK();
    DBG_OUT << "is_safe_mode=" << is_safe_mode << endl;
    hw_info(DBG_OUT);
    LittleFS.begin();
    setup_config();

    MDNS.addService("http", "tcp", SERVER_PORT_WEB);
    MDNS.begin(pDeviceName);
    setup_WebPages();
    setup_signals();

    LittleFS_info(DBG_OUT);
    setup_homie();

    ntpTime.init();
//------------------
    dht.setup(DHTPin, DHTesp::DHT22);
    setup_WIFIConnect();
    DBG_OUT << "Setup done" << endl;
}

void loop() {
    wifiStateSignal.loop();
    homie.Loop();
    ntpTime.loop();
    ADC_filter.loop();
    timeKeeper.loop();
    serverWeb.handleClient();
}

