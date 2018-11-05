//https://github.com/google/googletest.git
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <FS.h>

#include "CMainConfig.h"
#include "WebFaceWiFiConfig.h"
#include "CFrontendFS.h"
#include "frontend.h"
#include "cmd.h"

#define WIFI_SERVER
const char *ssid = "ITPwifi";
const char *password = "_RESTRICTED3db@ea";
ESP8266WebServer server(80);
WebFaceWiFiConfig WiFiConfig(server);
CMainConfig mainConfig(server);
CPresetsConfig presetsConfig(server);

void cli_info(int argc, char **argv) {
  Serial.println("FSInfo");
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

void setup() {
    WiFi.persistent(false);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200); delay(100);
    Serial.println("\n\nBOOTING ESP8266 ...");
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

	bool result = SPIFFS.begin();
	Serial.print("SPIFFS opened: ");Serial.println(result);
//	if(result)
	//	mainConfig.begin();
//Serial.println(mainConfig);
  cli_info(0, NULL);
	server.begin();

  presetsConfig.begin();
  Serial.println("Started");
  cmdInit();
  cmdAdd("info", cli_info);
  cmdAdd("ifconfig", cli_ifconfig);
}

void loop() {
  server.handleClient();
  cmdPoll();
}
