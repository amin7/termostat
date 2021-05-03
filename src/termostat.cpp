//https://github.com/google/googletest.git
/***
 * Screen
 * U8G2_SH1106_128X64_NONAME_F_HW_I2C
 * SCL - D1
 * SDA - D2
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <FS.h>

#include "CMainConfig.h"
#include "WebFaceWiFiConfig.h"
#include "frontend.h"

const char *ssid = "ITPwifi";
const char *password = "_RESTRICTED3db@ea";
ESP8266WebServer server(80);
WebFaceWiFiConfig WiFiConfig(server);
CMainConfig mainConfig(server);

void setup() {
    WiFi.persistent(false);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(100);
    Serial.println("\n\nBOOTING ESP8266 ...");
#ifdef _DISPLAY_
    u8g2.begin();
    u8g2.clearBuffer();                  // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
    u8g2.drawStr(0,10,"termostat booting");    // write something to the internal memory
    u8g2.drawStr(0,30,"termostat booting");
    u8g2.drawFrame(0, 0, 63, 27);
    u8g2.sendBuffer();                    // transfer internal memory to the display
#endif
#if false //cliend
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  WiFi.mode(WIFI_STA);

    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("Station IP address: ");
    Serial.println(WiFi.localIP());
#else
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.mode(WIFI_AP);
    WiFi.softAP("test", "esp12345");

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
#endif

//  server.on("/wifi", std::bind(&WiFiManager::handleWifi, &wiFiManager, true));
    //server.on("/", std::bind(&WiFiManager::handleRoot, &wiFiManager));
    //server.on("/",          handleWebsite);
//  server.on("/xml",       handleXML);
//  server.on("/setESPval", handleESPval);

    CFrontendFS::add(server, "/thtml1.html", ct_html, _frontend_thtml1_html_);
    CFrontendFS::add(server, "/term_main.js", ct_js, _frontend_term_main_js_);
    CFrontendFS::add(server, "/term_main.css", ct_css, _frontend_term_main_css_);
    CFrontendFS::add(server, "/", ct_html, _frontend_term_main_html_);
    CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html, _frontend_WiFiConfigEntry_html_);
    server.onNotFound([] {
        Serial.println("Error no handler");
        Serial.println(server.uri());
    });

    bool result = SPIFFS.begin();
    Serial.print("SPIFFS opened: ");
    Serial.println(result);
//	if(result)
    //	mainConfig.begin();
    Serial.println(mainConfig);
    FSInfo fsInfo;
    SPIFFS.info(fsInfo);
    Serial.print("totalBytes=");
    Serial.println(fsInfo.totalBytes);
    Serial.print("usedBytes=");
    Serial.println(fsInfo.usedBytes);
    Serial.print("blockSize=");
    Serial.println(fsInfo.blockSize);
    Serial.print("pageSize=");
    Serial.println(fsInfo.pageSize);
    Serial.print("maxOpenFiles=");
    Serial.println(fsInfo.maxOpenFiles);
    Serial.print("maxPathLength=");
    Serial.println(fsInfo.maxPathLength);
    server.begin();
}

void loop() {
    server.handleClient();
}
