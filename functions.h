// ========================================================================
#ifndef _functions_h_
#define _functions_h_
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String XML;
const int sliderMAX = 1;        // This sets the number of sliders you want
int sliderVal[sliderMAX] = {60}, ESPval[sliderMAX];

unsigned long wait000 = 0UL, wait001 = 1000UL;

ESP8266WebServer server(80);

String millis2time() {
  String Time = "";
  unsigned long ss;
  byte mm, hh;
  ss = millis() / 1000;
  hh = ss / 3600;
  mm = (ss - hh * 3600) / 60;
  ss = (ss - hh * 3600) - mm * 60;
  if (hh < 10)Time += "0";
  Time += (String)hh + ":";
  if (mm < 10)Time += "0";
  Time += (String)mm + ":";
  if (ss < 10)Time += "0";
  Time += (String)ss;
  return Time;
}

void buildXML() {
  XML = "<?xml version='1.0'?>";
  XML += "<xml>";
  XML += "<millistime>";
  XML += millis2time();
  XML += "</millistime>";
  for (int i = 0; i < sliderMAX; i++) {
    XML += "<sliderval" + (String)i + ">";
    XML += String(sliderVal[i]);
    XML += "</sliderval" + (String)i + ">";
    XML += "<ESPval" + (String)i + ">";
    ESPval[i] = 9 * (100 - sliderVal[i]) + 100;
    XML += String(ESPval[i]);
    XML += "</ESPval" + (String)i + ">";
  }
  XML += "</xml>";
  Serial.println(XML);
}

void handleWebsite() {
//  server.send(200, "text/html", webSite);
}

void handleXML() {
  buildXML();
  server.send(200, "text/xml", XML);
}

void handleESPval() {
  int sliderCNT = server.arg("cnt").toInt();
  sliderVal[sliderCNT] = server.arg("val").toInt();
  buildXML();
  server.send(200, "text/xml", XML);
  Serial.print(sliderCNT);
  Serial.print("  ");
  Serial.println(sliderVal[0]);
}


#endif _functions_h_
