//https://github.com/google/googletest.git
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#define ARDUINOJSON_ENABLE_PROGMEM 1
#define  ARDUINOJSON_DEFAULT_NESTING_LIMIT 10
//libs
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <FS.h>
#include "DHTesp.h"

//user libs
#include "CMainConfig.h"
#include "WebFaceWiFiConfig.h"
#include "CFrontendFS.h"
#include "frontend.h"
#include "cmd.h"
#include "CConfigFile.h"

#define WIFI_SERVER
const auto RelayPin = D6;
const auto DHTPin = D4;
const auto TermistorPin = A0;

const char *ssid = "ITPwifi";
const char *password = "_RESTRICTED3db@ea";
ESP8266WebServer server(80);
WebFaceWiFiConfig WiFiConfig(server);
CMainConfig mainConfig(server);
CPresetsConfig presetsConfig(server);
CConfigFile ConfigFile(server);
DHTesp dht;

void cli_info(int argc, char **argv) {
  ConfigFile.info();
  cmd_handler_list();
}

void cli_ifconfig(int argc, char **argv) {
#ifndef WIFI_SERVER //cliend
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Station IP address: ");
  Serial.println(WiFi.localIP());
#else
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
#endif
}

void cli_relay(int argc, char **argv) {
  if (2 == argc) {
    switch (*argv[1]) {
      case '0':
        digitalWrite(RelayPin, 0);
        break;
      case '1':
        digitalWrite(RelayPin, 1);
        break;
    }
  }
}

void cli_termo(int argc, char **argv) {
  Serial.print("dht status:");
  Serial.println(dht.getStatusString());
  Serial.print("Temperature= ");
  Serial.println(dht.getTemperature());
  Serial.print("Humidity= ");
  Serial.println(dht.getHumidity());

  auto ADCvalue = analogRead(TermistorPin);
  Serial.print("Analoge ");
  Serial.println(ADCvalue);
}

void setup() {
  WiFi.persistent(false);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, 0); //off
  pinMode(DHTPin, INPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\nBOOTING ESP8266 ...");
  dht.setup(DHTPin, DHTesp::DHT22);
#ifndef WIFI_SERVER //cliend
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  WiFi.mode(WIFI_STA);
#else
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP("test", "esp12345");
	WiFi.mode(WIFI_AP);
#endif
  cli_ifconfig(0, NULL);
//  server.on("/wifi", std::bind(&WiFiManager::handleWifi, &wiFiManager, true));
  //server.on("/", std::bind(&WiFiManager::handleRoot, &wiFiManager));
  //server.on("/",          handleWebsite);
//  server.on("/xml",       handleXML);
//  server.on("/setESPval", handleESPval);

	CFrontendFS::add(server, "/thtml1.html", ct_html,_frontend_thtml1_html_);
	CFrontendFS::add(server, "/term_main.js", ct_js,_frontend_term_main_js_);
	CFrontendFS::add(server, "/term_main.css", ct_css,_frontend_term_main_css_);
	CFrontendFS::add(server, "/", ct_html,_frontend_term_main_html_);
	CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html,_frontend_WiFiConfigEntry_html_);
	server.onNotFound([]{
			Serial.println("Error no handler");
			Serial.println(server.uri());
	});

	server.begin();
  ConfigFile.add("/presets.json", presetsConfig);
//  ConfigFile.begin();
  Serial.println("Started");
  cmdInit();
  cmdAdd("info", cli_info);
  cmdAdd("ifconfig", cli_ifconfig);
  cmdAdd("relay", cli_relay);
  cmdAdd("term", cli_termo);

}

void loop() {
  server.handleClient();
  cmdPoll();
}
