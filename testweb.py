#!/usr/bin/python3

import os
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
from urllib.parse import parse_qs
from urllib.parse import urlencode
import json
import argparse

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

handler ={}
def printHandlers():
    print("Handler list:");
    for rule in handler:
        if handler[rule] == None:
            print ("'" + rule + "'<None>")
        else:
            print ("'" + rule + "'<" + handler[rule].toString() + ">")

workPatch=""
# HTTPRequestHandler class
class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_Reply(self):
        o = urlparse(self.path)
        print(o)
        print(parse_qs(o.query))
        uir = o.path
        if uir not in handler:
            print('unknowFileTypeERROR')
            self.send_response(404)
            return

        rule=handler[uir];
        if rule == None:#stub
            self.do_HEAD()
            return

        print("rule="+rule.toString())
        try:
            fo = open(rule.file, "r")
        except:
            # doesn't exist
            print('FileNotFoundError')
            self.send_response(404)
        else:
            self.send_response(200)
            self.send_header("Content-type", rule.content_type)
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

def run(PORT):
    print('starting server...')
    server_address = ('127.0.0.1', PORT)
    httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
    printHandlers()

    print('running server... ')
    print('http://localhost:',PORT,sep='')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()


parser = argparse.ArgumentParser(description='no')
parser.add_argument('-c', dest='configFile', help='patch to config File',  required=True)
parser.add_argument('-p', dest='port',type=int,default=8081, help='server port', )
args = parser.parse_args()
configDir=os.path.dirname(args.configFile)+"/"
print("configDir="+configDir)
print("parce config file" )
with open(args.configFile) as data_file:
    data_item = json.load(data_file)

#add rules from wwwSourceDir
wwwSourceDir=configDir+data_item["wwwSourceDir"]+"/"
ignoredFiles=[];
print("wwwSourceDir="+wwwSourceDir)
for filename in os.listdir(wwwSourceDir):
    normFileName=os.path.normpath(wwwSourceDir + filename)
    extension = os.path.splitext(filename)[1][1:]
    if extension in fileExt:
        handler.update({"/"+filename: Route(fileExt[extension], normFileName)})
    else:
        ignoredFiles.append(normFileName)
for ignore in ignoredFiles:
    print ("file ignored "+ignore);

#add rules from json (rewrite wwwSourceDir)
for rule in data_item["handler"]:
    if "entry" not in rule:
        print("error no entry" )
        exit(1)
    if "file" not in rule:
        handler.update({rule["entry"]:None})
        continue
    filename=os.path.normpath(configDir+rule["file"]);
    content_type=""
    if "type" in rule:
        content_type=rule["type"]
    else:
        extension = os.path.splitext(filename)[1][1:]
        try:
            content_type = fileExt[extension]
        except:
            print(' unknowFileTypeERROR')
            exit(1)
    handler.update({rule["entry"]: Route(content_type, filename)})


#printHandlers()
run(args.port)

