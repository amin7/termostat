/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "functions.h"

//https://github.com/tzapu/WiFiManager.git

#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include "WebFaceWiFiConfig.h"


const char *ssid = "ITPwifi";
const char *password = "_RESTRICTED3db@ea";

WiFiManager wiFiManager;
WebFaceWiFiConfig WiFiConfig(server);

void setup() {
  WiFi.persistent(false);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); delay(100);
  Serial.println("\n\nBOOTING ESP8266 ...");
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

  server.on("/wifi", std::bind(&WiFiManager::handleWifi, &wiFiManager, true));
  //server.on("/", std::bind(&WiFiManager::handleRoot, &wiFiManager));
  //server.on("/",          handleWebsite);
  WiFiConfig.setup("/");
  server.on("/xml",       handleXML);
  server.on("/setESPval", handleESPval);
  server.begin();
}

void loop() {
  server.handleClient();
  if (millis() > wait001) {             // slider0 controls LED blink rate
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    wait001 = millis() + ESPval[0];
  }
}
