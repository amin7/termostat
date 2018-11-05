#ifndef _FRONT_END_
#define _FRONT_END_
//converted  date time= 2018-11-05 14:07:18.534744
const char* _frontend_term_main_css_ PROGMEM ={\
  "#button_schedule_hour{\n"\
    "border: 0px solid black;\n"\
    "color: black;\n"\
    "text-align: center;\n"\
    "text-decoration: none;\n"\
    "display: inline-block;\n"\
    "font-size: 14px;\n"\
    "cursor: pointer;\n"\
    "float: left;\n"\
"}\n"\
  "#temper_cur {\n"\
    "display: inline-block;\n"\
    "font-size: 32px;\n"\
    "float: left;\n"\
    "height:32px\n"\
"}\n"\
  "#temper_present {\n"\
   "color: green;\n"\
   "display: inline-block;\n"\
    "font-size: 14px;\n"\
    "float: left;\n"\
    "height:14px\n"\
"}\n"\
"#temper_ansent {\n"\
    "color: gray;\n"\
    "display: inline-block;\n"\
    "font-size: 14px;\n"\
    "float: left;\n"\
    "height:14px\n"\
"}\n"\
};
const char* _frontend_term_main_html_ PROGMEM ={\
"<!DOCTYPE html>\n"\
"<html>\n"\
    "<head>\n"\
        "<title>Termostat</title>\n"\
        "<script src=\"term_main.js\"></script>\n"\
        "<link rel=\"stylesheet\" href=\"term_main.css\">\n"\
    "</head>\n"\
    "<body onload=\"init()\">\n"\
        "<h1>state</h1>\n"\
        "<p id=\"date\"></p>\n"\
        "<div id=\"temper_cur\" >25.1</div>\n"\
        "<div >\n"\
            "<div id=\"temper_present\" >27.1</div>\n"\
            "<br/>\n"\
            "<div id=\"temper_ansent\" >24.1</div>\n"\
        "</div>\n"\
\
        "<div id=\"Presets\" >\n"\
            "<h2>Presets</h2>\n"\
            "<hr>\n"\
            "<div>\n"\
              "<button onclick=add_byWeekday()>by Weekday</button>\n"\
              "<button >Out till</button>\n"\
              "<button >today</button>\n"\
            "</div>\n"\
            "<ul id=PresetsList> </ul>\n"\
        "</div>\n"\
        "<button onclick=PresetSave()>Save</button>\n"\
        "<button onclick=PresetLoad()>Load</button>\n"\
    "</body>\n"\
"</html>\n"\
};
const char* _frontend_term_main_js_ PROGMEM ={\
"let dayOfWeekStr=[\"Monday\",\"Tuesday\",\"Wednesday\",\"Thursday\",\"Friday\",\"Saturday\",\"Sunday\"];\n"\
\
"xmlHttp=createXmlHttpObject();\n"\
\
  "function createXmlHttpObject(){\n"\
    "if(window.XMLHttpRequest){\n"\
      "xmlHttp=new XMLHttpRequest();\n"\
    "}else{\n"\
      "xmlHttp=new ActiveXObject(\'Microsoft.XMLHTTP\');\n"\
    "}\n"\
    "return xmlHttp;\n"\
  "}\n"\
\
  "function PresetLoad(){\n"\
      "let presetsList = document.getElementById(\"PresetsList\");\n"\
        "while (presetsList.firstChild) {\n"\
            "presetsList.removeChild(presetsList.firstChild);\n"\
          "}\n"\
\
      "var xh = new XMLHttpRequest();\n"\
      "xh.onreadystatechange = function(){\n"\
        "if (xh.readyState == 4){\n"\
          "if(xh.status == 200) {\n"\
            "var res = JSON.parse(xh.responseText);\n"\
            "console.log(res);\n"\
          "}\n"\
        "}\n"\
      "};\n"\
      "xh.open(\"GET\", \"/PresetLoad\", true);\n"\
      "xh.send(null);\n"\
    "}\n"\
\
\
"function PresetSave(){\n"\
    "listSerialize();\n"\
"//  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
"//	    xmlHttp.onreadystatechange=function(){\n"\
"//	      if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
"//	    	  console.log(\"saved ok\");\n"\
"//	      }\n"\
"//	    }\n"\
"//	var doc = document.getElementById(\"PresetsList\");\n"\
"//	let myJSON=null;\n"\
"//	if(doc.children.length){\n"\
"//		let obj=doc.children[0].controlData;\n"\
"//		myJSON = JSON.stringify(obj);\n"\
"//	}\n"\
"//	 var url = \"PresetAdd?data=\" + encodeURIComponent(myJSON);\n"\
"//\n"\
"//	 xmlHttp.open(\'GET\',url,true); //POST is more safely but ... harder to suuport from esp side\n"\
"//	 xmlHttp.setRequestHeader(\"Content-Type\", \"application/json;charset=UTF-8\");\n"\
"//	 console.log(url);\n"\
"//	 xmlHttp.send(null);\n"\
"//  }\n"\
"}\n"\
\
"function selectionList(parent,valList,initial){\n"\
    "this.Value=[];\n"\
    "const colorSelected=\"#fc6400\";\n"\
    "const colorSelection=\"#fc0000\";\n"\
    "const colorNotSelected=\"#00a3fc\";\n"\
    "const colorNotSelection=\"#0800fc\";\n"\
    "var isPressed=false;\n"\
    "var isSelected=false;\n"\
    "var selBeg,selEnd;\n"\
    "let myNode =document.createElement(\"div\");\n"\
    "parent.appendChild(myNode);\n"\
    "if(myNode==null)\n"\
        "return;\n"\
    "function dispaySelection(selBeg,selEnd,isSelected){\n"\
        "childNodes=myNode.childNodes;\n"\
        "i = childNodes.length;\n"\
\
        "while (i--) {\n"\
            "if (childNodes[i].getAttribute(\"class\") == \"button\") {\n"\
                "var button=childNodes[i];\n"\
                "var cur=parseInt(button.name);\n"\
                "if((cur>=selBeg)&&(cur<=selEnd)){\n"\
                    "button.style.backgroundColor = isSelected?colorSelection:colorNotSelection;\n"\
                "}else{ //show default state\n"\
                    "button.style.backgroundColor = (button.value==\"true\")?colorSelected:colorNotSelected;\n"\
                "}\n"\
\
            "}\n"\
        "}\n"\
    "}\n"\
        "this.doSelection= function(selBeg,selEnd,isSelected){\n"\
         "childNodes=myNode.childNodes\n"\
         "i = childNodes.length;\n"\
         "while (i--) {\n"\
             "var button=childNodes[i];\n"\
             "var cur=parseInt(button.name);\n"\
            "if((cur>=selBeg)&&(cur<=selEnd))\n"\
                "button.value=isSelected;\n"\
            "button.style.backgroundColor = (button.value==\"true\")?colorSelected:colorNotSelected;\n"\
            "this.Value[i]=(button.value==\"true\")?1:0;\n"\
         "}\n"\
         "}\n"\
    "this.moveState=function(button) {\n"\
        "if(isPressed){\n"\
            "selEnd=parseInt(button.name);\n"\
            "if(selBeg<=selEnd)\n"\
                "dispaySelection(selBeg,selEnd,isSelected);\n"\
            "else\n"\
                "dispaySelection(selEnd,selBeg,isSelected);\n"\
        "}\n"\
    "}\n"\
    "this.keyDown=function (button) {\n"\
         "isPressed=true;\n"\
         "if (button.value == \'false\') {\n"\
             "isSelected=true;\n"\
         "}\n"\
         "else {\n"\
             "isSelected=false;\n"\
         "}\n"\
         "selBeg=selEnd=parseInt(button.name);\n"\
         "dispaySelection(selBeg,selEnd,isSelected);\n"\
       "};\n"\
    "this.keyUp=function () {\n"\
         "if(isPressed){\n"\
             "if(selBeg<=selEnd)\n"\
               "this.doSelection(selBeg,selEnd,isSelected);\n"\
             "else\n"\
                 "this.doSelection(selEnd,selBeg,isSelected);\n"\
         "}\n"\
         "isPressed=false;\n"\
    "};\n"\
\
    "var obj = this;\n"\
       "for(var i=0;i<valList.length;i++){\n"\
            "this.Value.push(initial[i]);\n"\
            "let button=document.createElement(\"button\")\n"\
            "button.innerHTML = valList[i];\n"\
            "button.setAttribute(\"name\", i);\n"\
            "button.setAttribute(\"class\", \"button\");\n"\
            "button.setAttribute(\"id\", \"button_schedule_hour\");\n"\
\
            "button.addEventListener(\"mousedown\", function(){ obj.keyDown(button); });\n"\
         "button.addEventListener(\"mouseenter\", function(){ obj.moveState(button);});\n"\
\
         "button.value=initial[i]?true:false;\n"\
         "button.style.backgroundColor = (button.value==\"true\")?colorSelected:colorNotSelected;\n"\
            "myNode.appendChild(button);\n"\
       "}\n"\
       "window.addEventListener(\'mouseup\', function(event){obj.keyUp();});\n"\
"}\n"\
"function updateCurrDateTime(){\n"\
    "var options = {\n"\
            "weekday: \"long\", year: \"numeric\", month: \"short\",\n"\
            "day: \"numeric\", hour: \"2-digit\", minute: \"2-digit\",hour12: false\n"\
        "};\n"\
    "var date=new Date();\n"\
    "document.getElementById(\"date\").innerHTML = date.toLocaleTimeString([], options);\n"\
"}\n"\
"function htmlObj(html){\n"\
    "let el = document.createElement(\"span\");\n"\
    "el.innerHTML = html;\n"\
    "return el;\n"\
"}\n"\
\
"function byWeekday(placement){\n"\
    "let div=document.createElement(\"div\");\n"\
    "let initw=[0,0,0,0,0,1,1];\n"\
    "this.weekDay=new selectionList(div,dayOfWeekStr,initw);\n"\
    "div.appendChild(document.createElement(\"BR\"));\n"\
    "var valArray=[24];\n"\
    "for(var i=0;i<24;i++){\n"\
        "valArray[i]=\"\"+i;\n"\
    "}\n"\
    "let inith=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];\n"\
    "this.hours= new selectionList(div,valArray,inith);\n"\
    "div.appendChild(document.createElement(\"BR\"));\n"\
    "placement.appendChild(div);\n"\
"}\n"\
\
"function add_byWeekday(){\n"\
    "let presetsList = document.getElementById(\"PresetsList\");\n"\
    "let listItem=document.createElement(\"LI\");\n"\
    "listItem.weekday =new byWeekday(listItem);\n"\
    "listItem.appendChild(document.createElement(\"BR\"));\n"\
    "presetsList.insertBefore(listItem,presetsList.childNodes[0]);\n"\
"}\n"\
\
"function listSerialize(){\n"\
    "var cache = [];\n"\
    "var doc = document.getElementById(\"PresetsList\");\n"\
    "for (i = 0; i < doc.children.length; i++) {\n"\
        "let obj=doc.children[i].weekday;\n"\
        "let myJSON = JSON.stringify(obj);\n"\
        "cache.push(myJSON);\n"\
    "}\n"\
    "console.log(cache);\n"\
\
\
"}\n"\
\
"function init(){\n"\
    "updateCurrDateTime();\n"\
    "setInterval(\'updateCurrDateTime()\', 1000);\n"\
    "add_byWeekday();//for test\n"\
    "//PresetLoad();\n"\
"}\n"\
};
const char* _frontend_thtml1_html_ PROGMEM ={\
  "<!DOCTYPE HTML>\n"\
  "<html>\n"\
  "<META name=\'viewport\' content=\'width=device-width, initial-scale=1\'>\n"\
        "<title>Termostat</title>\n"\
  "<SCRIPT>\n"\
  "xmlHttp=createXmlHttpObject();\n"\
\
  "function createXmlHttpObject(){\n"\
    "if(window.XMLHttpRequest){\n"\
      "xmlHttp=new XMLHttpRequest();\n"\
    "}else{\n"\
      "xmlHttp=new ActiveXObject(\'Microsoft.XMLHTTP\');\n"\
    "}\n"\
    "return xmlHttp;\n"\
  "}\n"\
\
  "function process(){\n"\
    "if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
      "xmlHttp.onreadystatechange=function(){\n"\
        "if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
          "xmlDoc=xmlHttp.responseXML;\n"\
          "xmlmsg=xmlDoc.getElementsByTagName(\'millistime\')[0].firstChild.nodeValue;\n"\
          "document.getElementById(\'runtime\').innerHTML=xmlmsg;\n"\
          "xmlmsg=xmlDoc.getElementsByTagName(\'sliderval0\')[0].firstChild.nodeValue;\n"\
          "document.getElementById(\'slider0\').value=xmlmsg;\n"\
          "document.getElementById(\'Sliderval0\').innerHTML=xmlmsg;\n"\
          "xmlmsg=xmlDoc.getElementsByTagName(\'ESPval0\')[0].firstChild.nodeValue;\n"\
          "document.getElementById(\'ESPval0\').innerHTML=xmlmsg;\n"\
        "}\n"\
      "}\n"\
      "xmlHttp.open(\'PUT\',\'xml\',true);\n"\
      "xmlHttp.send(null);\n"\
    "}\n"\
    "setTimeout(\'process()\',1000);\n"\
  "}\n"\
\
  "function Slider(cnt){\n"\
    "sliderVal=document.getElementById(\'slider\'+cnt).value;\n"\
    "document.getElementById(\'Sliderval\'+cnt).innerHTML=sliderVal;\n"\
    "document.getElementById(\'ESPval\'+cnt).innerHTML=9*(100-sliderVal)+100;\n"\
    "if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
      "xmlHttp.open(\'PUT\',\'setESPval?cnt=\'+cnt+\'&val=\'+sliderVal,true);\n"\
      "xmlHttp.send(null);\n"\
    "}\n"\
  "}\n"\
\
  "function myFunction(){\n"\
      "var myNode = document.getElementById(\"list\");\n"\
      "var text = \"l\"+myNode.childNodes.length;\n"\
      "var li = document.createElement(\"LI\");\n"\
      "var att = document.createAttribute(\"onclick\");\n"\
      "att.value = \"myFunction()\";\n"\
      "li.setAttributeNode(att);\n"\
      "var node = document.createTextNode(text+\"***\");\n"\
      "li.appendChild(node);\n"\
\
      "myNode.appendChild(li);\n"\
\
    "}\n"\
\
  "function myFunctionClear(){\n"\
      "var myNode = document.getElementById(\"list\");\n"\
      "while (myNode.firstChild) {\n"\
          "myNode.removeChild(myNode.firstChild);\n"\
      "}\n"\
\
    "}\n"\
\
  "</SCRIPT>\n"\
\
  "<BODY onload=\'process()\'>\n"\
  "<BR>Change slider0 to control LED blink...<BR>\n"\
  "Runtime = <A ID=\'runtime\'></A><BR><BR>\n"\
  "<TABLE BORDER=1 style=\'text-align:center;border-collapse:collapse\'>\n"\
    "<TR>\n"\
    "<TD><BR><INPUT ID=\'slider0\' TYPE=\'range\' ONCHANGE=\'Slider(0)\'></TD>\n"\
    "<TD>Slidervalue0= <A ID=\'Sliderval0\'></A><BR>\n"\
    "ESPval0 = <A ID=\'ESPval0\'></A> milliseconds</TD>\n"\
    "</TR>\n"\
  "</TABLE>\n"\
"<form id=\"check_LEDs\" name=\"LED_form\">\n"\
    "<input type=\"checkbox\" name=\"chk_group[]\" value=\"value1\" />Value 1<br />\n"\
    "<input type=\"checkbox\" name=\"chk_group[]\" value=\"value2\" />Value 2<br />\n"\
    "<input type=\"checkbox\" name=\"chk_group[]\" value=\"value3\" />Value 3<br />\n"\
"</form>\n"\
\
    "Wifi networks list <button onclick=\"myFunction()\">refresh</button>\n"\
"<div id=\"container\">\n"\
  "<ul id=\"list\"></ul>\n"\
"</div>\n"\
    "<button onclick=\"myFunctionClear()\">clear </button><BR/>\n"\
    "Selected= <A ID=\'Selected\'></A><BR/>\n"\
  "</BODY>\n"\
  "</HTML>\n"\
};
const char* _frontend_WiFiConfigEntry_html_ PROGMEM ={\
  "<!DOCTYPE HTML>\n"\
  "<html>\n"\
  "<META name=\'viewport\' content=\'width=device-width, initial-scale=1\'>\n"\
        "<title>network</title>\n"\
  "<SCRIPT>\n"\
          "xmlHttp=createXmlHttpObject();\n"\
\
  "function createXmlHttpObject(){\n"\
    "if(window.XMLHttpRequest){\n"\
      "xmlHttp=new XMLHttpRequest();\n"\
    "}else{\n"\
      "xmlHttp=new ActiveXObject(\'Microsoft.XMLHTTP\');\n"\
    "}\n"\
    "return xmlHttp;\n"\
  "}\n"\
\
  "function selectSSID(SSID) {\n"\
        "var ssid=document.getElementById(\"Selected\");\n"\
        "ssid.value=SSID;\n"\
    "}\n"\
\
  "function connectSSID(){\n"\
      "if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
          "xmlHttp.open(\'PUT\',\'ConnectToWifi?SSCID=\\\"\'+document.getElementById(\"Selected\").value\n"\
                  "+\'\\\"&PWD=\\\"\'+ document.getElementById(\"PWD\").value\n"\
                  "+\'\\\"\',true);\n"\
          "xmlHttp.send(null);\n"\
        "}\n"\
  "}\n"\
  "function clearSSIDList(){\n"\
      "var myNode = document.getElementById(\"list\");\n"\
      "while (myNode.firstChild) {\n"\
          "myNode.removeChild(myNode.firstChild);\n"\
      "}\n"\
  "}\n"\
\
  "function refreshSSIDs(){\n"\
      "clearSSIDList();\n"\
      "var myNode = document.getElementById(\"list\");\n"\
      "var li = document.createElement(\"LI\");\n"\
      "var node = document.createTextNode(\"scanning...\");\n"\
      "li.appendChild(node);\n"\
\
      "myNode.appendChild(li);\n"\
    "if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
        "xmlHttp.onreadystatechange=function(){\n"\
          "if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
              "clearSSIDList();\n"\
\
              "wifiList= this.responseXML.getElementsByTagName(\"wifi\");\n"\
              "li = document.createElement(\"LI\");\n"\
              "node = document.createTextNode(\"len\");\n"\
              "li.appendChild(node);\n"\
\
              "for (var i=0;i<wifiList.length; i++) {\n"\
                  "var line=wifiList[i];\n"\
                  "var SSID = line.getAttributeNode(\"SSID\").value;\n"\
                  "var RSSI = parseInt(line.getAttributeNode(\"RSSI\").value);\n"\
                  "var RSSIverb=\"---\";\n"\
                  "if(-30<=RSSI){\n"\
                      "RSSIverb=\"Amazing\";\n"\
                  "}else if(-67<=RSSI){\n"\
                      "RSSIverb=\"Very Good\";\n"\
                  "}else if(-70<=RSSI){\n"\
                      "RSSIverb=\"Okay\";\n"\
                  "}else if(-80<=RSSI){\n"\
                      "RSSIverb=\"Not Good\";\n"\
                  "}else if(-90<=RSSI){\n"\
                      "RSSIverb=\"Unusable\";\n"\
                  "}\n"\
\
                  "var encryptted=\"\";\n"\
                  "if(parseInt(line.getAttributeNode(\"encryptionType\").value)!=7){\n"\
                      "encryptted=\"#\";\n"\
                  "}\n"\
\
                  "var li = document.createElement(\"LI\");\n"\
                  "var att = document.createAttribute(\"onclick\");\n"\
                  "var cmd=\"selectSSID(\'\"+SSID+\"\');\";\n"\
                  "att.value = cmd;\n"\
                  "li.setAttributeNode(att);\n"\
                  "var node = document.createTextNode(SSID+\"  \"+RSSI+\'dBm(\'+RSSIverb+\')\'+encryptted);\n"\
                  "li.appendChild(node);\n"\
\
                  "myNode.appendChild(li);\n"\
              "}\n"\
          "}\n"\
        "}\n"\
        "xmlHttp.open(\'GET\',\'ScanWifi\',true);\n"\
        "xmlHttp.send(null);\n"\
      "}\n"\
    "}\n"\
\
  "function myFunctionClear(){\n"\
      "var myNode = document.getElementById(\"list\");\n"\
      "while (myNode.firstChild) {\n"\
          "myNode.removeChild(myNode.firstChild);\n"\
      "}\n"\
\
    "}\n"\
\
  "</SCRIPT>\n"\
\
 "<BODY onload=\'refreshSSIDs()\'>\n"\
\
    "Wifi networks list <button onclick=\"refreshSSIDs()\">refresh</button>\n"\
"<div id=\"container\">\n"\
  "<ul id=\"list\"></ul>\n"\
"</div>\n"\
    "<button onclick=\"myFunctionClear()\">clear </button><BR/>\n"\
    "Selected=<input id=\"Selected\" type=\"text\" name=\"Selected\" value=\"sdf\"><BR/>\n"\
    "PWD=<input id=\"PWD\" type=\"password\" name=\"PDW\" value=\"\"><BR/>\n"\
    "<button onclick=\"connectSSID()\">Connect </button><BR/>\n"\
  "</BODY>\n"\
  "</HTML>\n"\
};

//converted list
//  CFrontendFS::add(server, "/term_main.css", ct_css,_frontend_term_main_css_);
//  CFrontendFS::add(server, "/term_main.html", ct_html,_frontend_term_main_html_);
//  CFrontendFS::add(server, "/term_main.js", ct_js,_frontend_term_main_js_);
//  CFrontendFS::add(server, "/thtml1.html", ct_html,_frontend_thtml1_html_);
//  CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html,_frontend_WiFiConfigEntry_html_);
#endif
//EOF
