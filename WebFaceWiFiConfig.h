/*
 * NetworkDlg.h
 *
 *  Created on: Oct 12, 2017
 *      Author: ominenko
 */

#ifndef WEBFACEWIFICONFIG_H_
#define WEBFACEWIFICONFIG_H_

#include <ESP8266WebServer.h>
#include "CFrontendFS.h"

class WebFaceWiFiConfig {
	ESP8266WebServer &server;
	String XML;
	void xmlScanWifi();
public:
	WebFaceWiFiConfig(ESP8266WebServer &_server,const char *entryPoint);
	virtual ~WebFaceWiFiConfig(){};
};

#endif /* WEBFACEWIFICONFIG_H_ */
