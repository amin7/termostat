//converted from  WiFiConfigEntry.html  getsize= 2317
const char* _WiFiConfigEntry_html_ PROGMEM ={\
  "<!DOCTYPE HTML>\n"\
  "<html>\n"\
  "<META name='viewport' content='width=device-width, initial-scale=1'>\n"\
        "<title>network</title>\n"\
  "<SCRIPT>\n"\
  "xmlHttp=createXmlHttpObject();\n"\
""\
  "function createXmlHttpObject(){\n"\
    "if(window.XMLHttpRequest){\n"\
      "xmlHttp=new XMLHttpRequest();\n"\
    "}else{\n"\
      "xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n"\
    "}\n"\
    "return xmlHttp;\n"\
  "}\n"\
""\
  "function selectSSID(SSID) {\n"\
"var ssid=document.getElementById(\"Selected\");\n"\
"ssid.value=SSID;\n"\
"}\n"\
  ""\
  "function refreshSSIDs(){\n"\
"var myNode = document.getElementById(\"list\");\n"\
"var li = document.createElement(\"LI\");\n"\
"var node = document.createTextNode(\"scanning...\");\n"\
"li.appendChild(node);\n"\
 ""\
"myNode.appendChild(li);\n"\
"if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
"xmlHttp.onreadystatechange=function(){\n"\
"if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
   ""\
"while (myNode.firstChild) {\n"\
"myNode.removeChild(myNode.firstChild);\n"\
"}\n"\
""\
"wifiList= xmlDoc.getElementsByTagName(\"wifi\");\n"\
"li = document.createElement(\"LI\");\n"\
"node = document.createTextNode(\"len\");\n"\
"li.appendChild(node);\n"\
""\
"for (i = 0; i < wifiList.length; i++) {\n"\
"var text = \"l\"+myNode.childNodes.length;\n"\
"var li = document.createElement(\"LI\");\n"\
"var att = document.createAttribute(\"onclick\");\n"\
"var cmd=\"selectSSID('\"+text+\"');\";\n"\
"att.value = cmd;\n"\
"li.setAttributeNode(att);\n"\
"var node = document.createTextNode(text+\"***\");\n"\
"li.appendChild(node);\n"\
""\
"myNode.appendChild(li);\n"\
"}\n"\
"}\n"\
"}\n"\
"xmlHttp.open('PUT','xmlScanWifi',true);\n"\
"xmlHttp.send(null);\n"\
"}\n"\
"}\n"\
  ""\
  "function myFunctionClear(){\n"\
"var myNode = document.getElementById(\"list\");\n"\
"while (myNode.firstChild) {\n"\
"myNode.removeChild(myNode.firstChild);\n"\
"}\n"\
""\
"}\n"\
""\
  "</SCRIPT>\n"\
""\
 "<BODY onload='refreshSSIDs()'>\n"\
  ""\
"Wifi networks list <button onclick=\"refreshSSIDs()\">refresh</button>\n"\
"<div id=\"container\">\n"\
  "<ul id=\"list\"></ul>\n"\
"</div>\n"\
"<button onclick=\"myFunctionClear()\">clear </button><BR/>\n"\
"Selected=<input id=\"Selected\" type=\"text\" name=\"Selected\" value=\"sdf\"><BR/>\n"\
"PWD=<input type=\"password\" name=\"PDW\" value=\"\"><BR/>\n"\
"<button onclick=\"myFunctionClear()\">Connect </button><BR/>\n"\
  "</BODY>\n"\
  "</HTML>\n"\
};
// End WiFiConfigEntry.html writedsz 2317
