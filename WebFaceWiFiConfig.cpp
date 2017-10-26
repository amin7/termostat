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

void WebFaceWiFiConfig::htmlEntryPage() {
  server.send(200, "text/html", _WiFiConfigEntry_html_);
}

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

void WebFaceWiFiConfig::setup(const char *entryPoint){
	server.on(entryPoint, std::bind(&WebFaceWiFiConfig::htmlEntryPage, this));
	server.on("/ScanWifi", std::bind(&WebFaceWiFiConfig::xmlScanWifi, this));
}
