/*
 * CFrontendFS.h
 *
 *  Created on: Nov 8, 2017
 *      Author: ominenko
 */

#ifndef CFRONTENDFS_H_
#define CFRONTENDFS_H_
#include <ESP8266WebServer.h>

typedef enum{
	 ct_html=0,
	 ct_xml,
	 ct_js,
	 ct_css,
	 ct_json,
	 ct_last
}tContent;
/***
 *  wrapper to discover web pages
 *
 */
class CFrontendFS {
	ESP8266WebServer &server;
	const char* contentType;
	const char* pContent;
	void send();
	CFrontendFS(ESP8266WebServer &server,const char* URI,const char* contentType ,const char* pContent);
public:
	static bool add(ESP8266WebServer &server,const char* URI,tContent contentType,const char* pContent);
	virtual ~CFrontendFS();
};

#endif /* CFRONTENDFS_H_ */
