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
//https://github.com/google/googletest.git
#include <Arduino.h>
#include <U8g2lib.h> //https://github.com/olikraus/U8g2_Arduino.git
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "functions.h"
#include <Wire.h>

#include "CPresets.h"

//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_64X48_ER_F_HW_I2C  u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered

#include "WebFaceWiFiConfig.h"
#include "CFrontendFS.h"
#include "frontend.h"


const char *ssid = "ITPwifi";
const char *password = "_RESTRICTED3db@ea";

WebFaceWiFiConfig WiFiConfig(server);

void setup() {
    WiFi.persistent(false);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200); delay(100);
    Serial.println("\n\nBOOTING ESP8266 ...");
    u8g2.begin();
    u8g2.clearBuffer();                  // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
    u8g2.drawStr(0,10,"termostat booting");    // write something to the internal memory
    u8g2.drawStr(0,30,"termostat booting");
    u8g2.drawFrame(0, 0, 63, 27);
    u8g2.sendBuffer();                    // transfer internal memory to the display
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

	CFrontendFS::add(server, "/thtml1.html", ct_html,_frontend_thtml1_html_);
	CFrontendFS::add(server, "/term_main.js", ct_js,_frontend_term_main_js_);
	CFrontendFS::add(server, "/term_main.css", ct_css,_frontend_term_main_css_);
	CFrontendFS::add(server, "/", ct_html,_frontend_term_main_html_);
	CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html,_frontend_WiFiConfigEntry_html_);

	server.begin();
	Serial.println("setup done");
}

void loop() {
  server.handleClient();
  if (millis() > wait001) {             // slider0 controls LED blink rate
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    wait001 = millis() + ESPval[0];
  }
}
