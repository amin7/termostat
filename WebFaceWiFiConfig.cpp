/*
 * NetworkDlg.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: ominenko
 */

#include "WebFaceWiFiConfig.h"
#include "WiFiConfigEntry.h"
const char* XML_BEGIN PROGMEM ="<?xml version='1.0'?>\n<xml>";
const char* XML_END PROGMEM ="</xml>";

WebFaceWiFiConfig::WebFaceWiFiConfig(ESP8266WebServer &_server,const char *entryPoint):
		server(_server){
	CFrontendFS::add(server, entryPoint, ct_html, _WiFiConfigEntry_html_);
	server.on("/ScanWifi", std::bind(&WebFaceWiFiConfig::xmlScanWifi, this));
	};

void WebFaceWiFiConfig::xmlScanWifi() {
 Serial.println("scan begin");
  int n = WiFi.scanNetworks();
  XML = XML_BEGIN;
  Serial.println("scan done");
  for (int i = 0; i < n; ++i)
  {
	 XML +="<wifi SSID= '";
	 XML +=WiFi.SSID(i);
	 XML +="' RSSI= '";
	 XML +=WiFi.RSSI(i);
	 XML +="' encryptionType= '";
	 XML +=WiFi.encryptionType(i);
	 XML +="'/>";
   }
  XML+=XML_END;
  Serial.println(XML);
  server.send(200, "text/xml", XML);
}

