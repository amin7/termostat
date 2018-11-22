/*
 * CFrontendFS.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: ominenko
 */

#include "CFrontendFS.h"
const char* strContentType[] PROGMEM={
    "text/html",
    "text/xml",
    "application/javascript",
    "text/css",
    "application/json",
    "image/x-icon"
};

void CFrontendFS::send(){
  if (contentLength_) {
    server.send_P(200, contentType, pContent, contentLength_);
  } else {
    server.send_P(200, contentType, pContent);
  }
}
CFrontendFS::CFrontendFS(ESP8266WebServer &server, const char* URI, const char* contentType, const char* pContent, size_t contentLength) :
    server(server), contentType(contentType), pContent(pContent), contentLength_(contentLength) {
	server.on(URI,std::bind(&CFrontendFS::send, this));

}
CFrontendFS::~CFrontendFS(){

}
bool CFrontendFS::add(ESP8266WebServer &server, const char* URI, tContent contentType, const char* pContent, size_t contentLength) {
	if(contentType>=ct_last){
		return 1;
	}
  auto handler = new CFrontendFS(server, URI, strContentType[contentType], pContent, contentLength);
	return 0;
}
