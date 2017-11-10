#!/usr/bin/python3
#TODO move handler to setarate file
#TODO start directory config

import os
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
from urllib.parse import parse_qs
from urllib.parse import urlencode
import json

fileExt={
    "html"  :"text/html",
    "xml"   :"text/xml",
    "js"    :"application/javascript",
    "css"   :"text/css",
    "json"  :"application/json"
}

class Route(object):
    content_type = ""
    file = ""
    def __init__(self, content_type, file):
        self.content_type = content_type
        self.file = file
    def toString(self):
        return "File Name="+self.file+", content_type="+self.content_type

class RouteDef(Route):#get type from file extention
    def __init__(self, file):
        extension = os.path.splitext(file)[1][1:]
        try:
            content_type = fileExt[extension]
            print(content_type)
            super(RouteDef, self).__init__(content_type, file)
        except:
            print(' unknowFileTypeERROR')



handler = {
#   "/"             : Route("text/html", "WiFiConfigEntry.html"),
   "/"             : RouteDef("term_main.html"),
   "/ScanWifi"     : RouteDef("xmlScanWifi.xml"),
   "/ConnectWifi"  : Route("text/xml", "xmlConnectWifi.xml"),
   "/saveSchedule"  : Route("", ""),
}


PORT=8081 
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_Reply(self):
        o = urlparse(self.path)
        print(o)
        print(parse_qs(o.query))
        content_type = ""
        file = o.path
        if file in handler:
            rule=handler[file];
            print("rule="+rule.toString())
            if rule.file == "":#stub
                self.do_HEAD()
                return
            content_type=rule.content_type
            file=rule.file
        else: #get data from extention
            extension = os.path.splitext(file)[1][1:]
            file=file.strip("/")
            try:
                content_type=fileExt[extension]
            except:
                print('unknowFileTypeERROR')
                self.send_response(404)
                return
        print("file="+file+" type="+content_type)
        try:
            fo = open(file, "r")
        except:
            # doesn't exist
            print('FileNotFoundError')
            self.send_response(404)
        else:
            self.send_response(200)
            self.send_header("Content-type", content_type)
            self.end_headers()
            for line in fo:
                self.wfile.write(bytes(line, "utf8"))
            fo.close()
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers() 
    def do_GET(self):
        self.do_Reply()
    def do_PUT(self):
        self.do_Reply()

def run():
    print('starting server...')
    server_address = ('127.0.0.1', PORT)
    httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
    print('running server... ')
    print('http://localhost:',PORT,sep='')
    print("Handler list:");
    for key in handler:
        rule = handler[key];
        print(key+"(" + rule.toString()+")")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
 
run()

