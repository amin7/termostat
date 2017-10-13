#!/usr/bin/python3
import os
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer

PORT=8081 
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers() 
    def do_GET(self):
        print(self.path)

        self.send_response(200)
 
        # Send headers
        self.send_header('Content-type','text/html')
        self.end_headers()
        # Send message back to client
        fo = open("WiFiConfigEntry.html", "r")
        for line in fo:
           self.wfile.write(bytes(line, "utf8"))
        return
    def do_PUT(self):
        do_GET(self)

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

