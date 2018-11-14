#ifndef _FRONT_END_
#define _FRONT_END_
//converted  date time= 2018-11-14 19:38:33.551184
//cmd gen: D:\user\hobby\git\termostat\text2code.py -D frontend/
const char* _frontend_def_main_config_json_ PROGMEM ={\
"{\n"\
   "\"heat_mode\": 0,\n"\
   "\"term_vacation\":10,\n"\
   "\"term_night\":16,\n"\
   "\"term_day\":24,\n"\
   "\"term_max\":40\n"\
"}\n"\
};
const char* _frontend_def_preset_json_ PROGMEM ={\
"{\n"\
  "\"Presets\": [\n"\
    "{\n"\
      "\"weekDay\": 1,\n"\
      "\"hours\": 2\n"\
    "},\n"\
    "{\n"\
      "\"weekDay\": 3,\n"\
      "\"hours\": 0\n"\
    "}\n"\
  "]\n"\
"}\n"\
};
const char* _frontend_def_termistor_json_ PROGMEM ={\
"{\n"\
"\"offset\": 0,\n"\
 "\"points\": [\n"\
 "{177:24.4},{183:26.10},{235:36.6}]\n"\
"}\n"\
};
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
  "#state {\n"\
    "font-size: 32px;\n"\
"}\n"\
\
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
    "<fieldset>\n"\
        "<legend>State</legend>\n"\
        "heat_mode: <a id=\"heat_mode\"></a><br>\n"\
        "air_term: <a id=\"air_term\"></a>  &#8451;\n"\
        "air_humm: <a id=\"air_humm\"></a> %<br>\n"\
        "floor_term: <a id=\"floor_term\"></a> &#8451;<br>\n"\
        "target_term: <a id=\"target_term\"></a> &#8451;<br>\n"\
        "heater:<a id=\"heater_on\"></a><br>\n"\
        "time_status: <a id=\"time_status\"></a> <a id=\"time\"></a><br>\n"\
    "</fieldset>\n"\
   "<fieldset>\n"\
        "<legend>Control</legend>\n"\
        "<div class=\"btn-group\">\n"\
          "<button  class=\"btn\" id=\"mode_off\" onclick=SetHeatMode(0)>Off</button>\n"\
          "<button  class=\"btn\" id=\"mode_schedule\" onclick=SetHeatMode(1)>Schedule</button>\n"\
          "<button  class=\"btn\" id=\"mode_vocation\" onclick=SetHeatMode(2)>Vocation</button>\n"\
          "<button  class=\"btn\" id=\"mode_in\" onclick=SetHeatMode(3)>in</button>\n"\
          "<button  class=\"btn\" id=\"mode_out\" onclick=document.getElementById(\"myDialog\").showModal()>out</button>\n"\
        "</div>\n"\
        "<a id=\"mode_ext_str\"></a><br>\n"\
        "<br>\n"\
        "<fieldset>\n"\
            "<legend>Temperatures</legend>\n"\
            "term_vacation <input type=\"number\" min=10 max=35 id = \"term_vacation\"> &#8451;<br>\n"\
            "term_night <input type=\"number\" min=10 max=35 id = \"term_night\"> &#8451;<br>\n"\
            "term_day <input type=\"number\" min=10 max=35 id = \"term_day\"> &#8451;<br>\n"\
            "term_max <a id = \"term_max\"></a> &#8451;<br>\n"\
        "</fieldset>\n"\
       "<button onclick=MainConfigSave()>Save</button>\n"\
       "<button onclick=MainConfigLoad()>Load</button>\n"\
       "</fieldset>\n"\
       "<fieldset>\n"\
           "<legend>Presets</legend>\n"\
           "<ul id=PresetsList> </ul>\n"\
           "<button onclick=PresetSave()>Save</button>\n"\
           "<button onclick=PresetLoad()>Load</button>\n"\
       "</fieldset>\n"\
\
      "<dialog id=\"myDialog\">This is a dialog window\n"\
        "<button >Show dialog esc exit</button>\n"\
        "</dialog>\n"\
\
    "</body>\n"\
"</html>\n"\
};
const char* _frontend_term_main_js_ PROGMEM ={\
"let dayOfWeekStr=[\"Monday\",\"Tuesday\",\"Wednesday\",\"Thursday\",\"Friday\",\"Saturday\",\"Sunday\"];\n"\
"const colorSelected=\"#fc6400\";\n"\
"const colorSelection=\"#fc0000\";\n"\
"const colorNotSelected=\"#00a3fc\";\n"\
"const colorNotSelection=\"#0800fc\";\n"\
\
"let heat_mode_ids=[\"mode_off\",\"mode_schedule\",\"mode_vocation\",\"mode_in\",\"mode_out\"];\n"\
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
            "add_Presets(res);\n"\
          "}\n"\
        "}\n"\
      "};\n"\
      "xh.open(\"GET\", \"/ConfigLoad?name=presets\", true);\n"\
      "xh.send(null);\n"\
    "}\n"\
\
  "function StatusLoad(){\n"\
      "var xh = new XMLHttpRequest();\n"\
      "xh.onreadystatechange = function(){\n"\
        "if (xh.readyState == 4){\n"\
          "if(xh.status == 200) {\n"\
            "var res = JSON.parse(xh.responseText);\n"\
            "console.log(res);\n"\
            "document.getElementById(\"air_term\").innerHTML=res[\"air_term\"];\n"\
            "document.getElementById(\"air_humm\").innerHTML=res[\"air_humm\"];\n"\
            "document.getElementById(\"floor_term\").innerHTML=res[\"floor_term\"];\n"\
            "document.getElementById(\"target_term\").innerHTML=res[\"target_term\"];\n"\
            "document.getElementById(\"time_status\").innerHTML=res[\"time_status\"];\n"\
            "updateCurrDateTime(res[\"time\"]*1000);\n"\
            "document.getElementById(\"heater_on\").innerHTML=res[\"heater_on\"];\n"\
          "}\n"\
        "}\n"\
      "};\n"\
      "xh.open(\"GET\", \"/ConfigLoad?name=status\", true);\n"\
      "xh.send(null);\n"\
    "}\n"\
\
"function PresetSave(){\n"\
  "if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
    "xmlHttp.onreadystatechange=function(){\n"\
      "if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
          "console.log(\"saved ok\");\n"\
      "}\n"\
    "}\n"\
    "let myJSON = new Object;\n"\
    "myJSON.Presets=[];\n"\
    "var doc = document.getElementById(\"PresetsList\");\n"\
    "for (i = 0; i < doc.children.length; i++) {\n"\
        "let preset = new Object;\n"\
        "preset.weekDay=doc.children[i].preset.weekDay.getValue();\n"\
        "preset.hours=doc.children[i].preset.hours.getValue();\n"\
        "myJSON.Presets.push(preset);\n"\
    "}\n"\
    "var data = JSON.stringify(myJSON);\n"\
    "xmlHttp.open(\'PUT\',\"/ConfigSave?name=presets\",true);\n"\
    "xmlHttp.setRequestHeader(\"Content-Type\", \"application/json\");\n"\
    "xmlHttp.send(data);\n"\
    "console.log(data);\n"\
  "}\n"\
"}\n"\
\
"var heat_mode=0;\n"\
"function SetHeatMode(mode){\n"\
    "heat_mode=mode;\n"\
    "for(let ind=0;ind<heat_mode_ids.length;ind++){\n"\
        "document.getElementById(heat_mode_ids[ind]).style.backgroundColor = (ind==mode)?colorSelection:document.body.style.backgroundColor;\n"\
    "}\n"\
"}\n"\
\
\
"function MainConfigLoad(){\n"\
    "var xh = new XMLHttpRequest();\n"\
    "xh.onreadystatechange = function(){\n"\
      "if (xh.readyState == 4){\n"\
        "if(xh.status == 200) {\n"\
          "var res = JSON.parse(xh.responseText);\n"\
          "console.log(res);\n"\
          "let mode=res[\"heat_mode\"];\n"\
          "SetHeatMode(mode)\n"\
          "document.getElementById(\"heat_mode\").innerHTML=heat_mode_ids[mode];\n"\
          "document.getElementById(\"term_vacation\").value=res[\"term_vacation\"];\n"\
          "document.getElementById(\"term_night\").value=res[\"term_night\"];\n"\
          "document.getElementById(\"term_day\").value=res[\"term_day\"];\n"\
          "document.getElementById(\"term_max\").innerHTML=res[\"term_max\"];\n"\
        "}\n"\
      "}\n"\
    "};\n"\
    "xh.open(\"GET\", \"/ConfigLoad?name=mainconfig\", true);\n"\
    "xh.send(null);\n"\
  "}\n"\
\
"function MainConfigSave(){\n"\
"if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n"\
    "xmlHttp.onreadystatechange=function(){\n"\
      "if(xmlHttp.readyState==4&&xmlHttp.status==200){\n"\
          "console.log(\"saved ok\");\n"\
      "}\n"\
    "}\n"\
    "let myJSON = new Object;\n"\
    "myJSON[\"heat_mode\"]=heat_mode;\n"\
    "myJSON[\"term_vacation\"]=document.getElementById(\"term_vacation\").value;\n"\
    "myJSON[\"term_night\"]=document.getElementById(\"term_night\").value;\n"\
    "myJSON[\"term_day\"]=document.getElementById(\"term_day\").value;\n"\
\
    "var data = JSON.stringify(myJSON);\n"\
    "xmlHttp.open(\'PUT\',\"/ConfigSave?name=mainconfig\",true);\n"\
    "xmlHttp.setRequestHeader(\"Content-Type\", \"application/json\");\n"\
    "xmlHttp.send(data);\n"\
    "console.log(data);\n"\
    "MainConfigLoad(); //loopback\n"\
"}\n"\
"}\n"\
\
"function selectionList(parent,valList,initial){\n"\
    "var isPressed=false;\n"\
    "var isSelected=false;\n"\
    "var selBeg,selEnd;\n"\
    "let myNode =document.createElement(\"div\");\n"\
    "parent.appendChild(myNode);\n"\
    "if(myNode==null)\n"\
        "return;\n"\
    "this.getValue= function() {\n"\
        "let bitmap=0;\n"\
        "for (var index in myNode.childNodes) {\n"\
            "if(myNode.childNodes[index].value==\"true\"){\n"\
                "bitmap+=(1<<index);\n"\
            "}\n"\
           "}\n"\
        "return bitmap;\n"\
    "}\n"\
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
       "for(var i=0;i<valList.length;i++)\n"\
       "{\n"\
           "let isSet=initial&(1<<i)?true:false;\n"\
            "let button=document.createElement(\"button\")\n"\
            "button.innerHTML = valList[i];\n"\
            "button.setAttribute(\"name\", i);\n"\
            "button.setAttribute(\"class\", \"button\");\n"\
            "button.setAttribute(\"id\", \"button_schedule_hour\");\n"\
\
            "button.addEventListener(\"mousedown\", function(){ obj.keyDown(button); });\n"\
         "button.addEventListener(\"mouseenter\", function(){ obj.moveState(button);});\n"\
\
         "button.value=isSet;\n"\
         "button.style.backgroundColor = (button.value==\"true\")?colorSelected:colorNotSelected;\n"\
            "myNode.appendChild(button);\n"\
       "}\n"\
       "window.addEventListener(\'mouseup\', function(event){obj.keyUp();});\n"\
"}\n"\
"function updateCurrDateTime(timestamt){\n"\
    "var options = {\n"\
            "weekday: \"long\", year: \"numeric\", month: \"short\",\n"\
            "day: \"numeric\", hour: \"2-digit\", minute: \"2-digit\",hour12: false\n"\
        "};\n"\
    "var date=new Date(timestamt);\n"\
    "document.getElementById(\"time\").innerHTML = date.toUTCString([], options);\n"\
"}\n"\
"function htmlObj(html){\n"\
    "let el = document.createElement(\"span\");\n"\
    "el.innerHTML = html;\n"\
    "return el;\n"\
"}\n"\
\
"function preset(placement,initVal){\n"\
    "let div=document.createElement(\"div\");\n"\
    "this.weekDay=new selectionList(div,dayOfWeekStr,initVal.weekDay);\n"\
    "div.appendChild(document.createElement(\"BR\"));\n"\
    "var valArray=[24];\n"\
    "for(var i=0;i<24;i++){\n"\
        "valArray[i]=\"\"+i;\n"\
    "}\n"\
    "this.hours= new selectionList(div,valArray,initVal.hours);\n"\
    "div.appendChild(document.createElement(\"BR\"));\n"\
    "placement.appendChild(div);\n"\
"}\n"\
\
"function add_Presets(config){\n"\
    "let presetsList = document.getElementById(\"PresetsList\");\n"\
    "for (var key in config.Presets) {\n"\
        "let listItem=document.createElement(\"LI\");\n"\
        "listItem.preset =new preset(listItem,config.Presets[key]);\n"\
        "listItem.appendChild(document.createElement(\"BR\"));\n"\
        "presetsList.appendChild(listItem);\n"\
    "}\n"\
"}\n"\
\
"function init(){\n"\
    "MainConfigLoad();\n"\
    "PresetLoad();\n"\
    "StatusLoad();\n"\
    "setInterval(\'StatusLoad()\', 5000);\n"\
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
//  CFrontendFS::add(server, "/def_main_config.json", ct_json,_frontend_def_main_config_json_);
//  CFrontendFS::add(server, "/def_preset.json", ct_json,_frontend_def_preset_json_);
//  CFrontendFS::add(server, "/def_termistor.json", ct_json,_frontend_def_termistor_json_);
//  CFrontendFS::add(server, "/term_main.css", ct_css,_frontend_term_main_css_);
//  CFrontendFS::add(server, "/term_main.html", ct_html,_frontend_term_main_html_);
//  CFrontendFS::add(server, "/term_main.js", ct_js,_frontend_term_main_js_);
//  CFrontendFS::add(server, "/thtml1.html", ct_html,_frontend_thtml1_html_);
//  CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html,_frontend_WiFiConfigEntry_html_);
//file ignored frontend/termostat.png
#endif
//EOF
