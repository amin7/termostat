#!/usr/bin/python3
import os
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer
class Route(object):
    content_type = ""
    file = ""
    def __init__(self, content_type, file):
        self.content_type = content_type
        self.file = file
    def toString(self):
        return "File Name="+self.file+", content_type="+self.content_type

handler = {
    "/"             : Route("text/html", "WiFiConfigEntry.html"),
    "/ScanWifi"     : Route("text/xml", "xmlScanWifi.xml"),
    "/ConnectWifi"  : Route("text/xml", "xmlConnectWifi.xml"),
}


PORT=8081 
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_Reply(self):
        print(self.path)
        if self.path in handler:
            repl=handler[self.path]
            print(" "+repl.toString())
            try:
                fo = open(repl.file, "r")
            except:
                # doesn't exist
                print('FileNotFoundError')
                self.send_response(404)
            else:
                self.send_response(200)
                self.send_header("Content-type", repl.content_type)
                self.end_headers()
                for line in fo:
                    self.wfile.write(bytes(line, "utf8"))
                fo.close()
        else:
            print(' No handler')
            self.send_response(404)



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
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
 
run()

