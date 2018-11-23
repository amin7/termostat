#ifndef _FRONT_END_
#define _FRONT_END_
//converted  date time= 2018-11-23 11:48:43.211323
//cmd gen: D:\personal\git\termostat\text2code.py -D frontend/
const char* _frontend_def_preset_json_ PROGMEM ={
"{\"Presets\":[\n"\
"{\"weekDay\":31,\"hours\":4063616},\n"\
"{\"weekDay\":96,\"hours\":4163328}\n"\
"]}\n"\
};
const char* _frontend_def_termistor_json_ PROGMEM ={
"{\n"\
"\"offset\": 0,\n"\
 "\"points\": [\n"\
"{\"383\": 0},\n"\
"{\"546\": 10},\n"\
"{\"726\": 20},\n"\
"{\"798\": 24},\n"\
"{\"816\": 25},\n"\
"{\"834\": 26},\n"\
"{\"904\": 30},\n"\
"{\"987\": 35},\n"\
"{\"1019\": 37},\n"\
"{\"1023\": 40}\n"\
"]\n"\
"}\n"\
};
const char* _frontend_term_main_css_ PROGMEM ={
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
"#mode_in_out_mode_bt{\n"\
    "float: left;\n"\
    "padding:2px;\n"\
"}\n"\
\
"#mode_in_out_time_bt{\n"\
    "padding:2px;\n"\
"}\n"\
};
const char* _frontend_term_main_html_ PROGMEM ={
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
        "desired_term: <a id=\"desired_temperature\"></a> &#8451;<br>\n"\
        "heater:<a id=\"heater_on\"></a><br>\n"\
        "time_status: <a id=\"time_status\"></a> <a id=\"time\"></a><br>\n"\
    "</fieldset>\n"\
    "<fieldset>\n"\
   "<legend>Control</legend>\n"\
      "<input type=\"checkbox\" id=\"control_is_on\">On<br>\n"\
       "term_vacation <input type=\"number\" min=10 max=35 id = \"term_vacation\"> &#8451;<br>\n"\
       "term_night <input type=\"number\" min=10 max=35 id = \"term_night\"> &#8451;<br>\n"\
       "term_day <input type=\"number\" min=10 max=35 id = \"term_day\"> &#8451;<br>\n"\
       "term_max <a id = \"term_max\"></a> &#8451;<br>\n"\
       "<br>\n"\
              "<fieldset>\n"\
          "<legend>Scheduler</legend>\n"\
               "<div id=\"mode_in_out\">\n"\
               "<div id=\"mode_in_out_mode_bt\">\n"\
                "<button class=\"btn\" id=\"mode_in\" onclick=SetInOutMode(1)>in</button>\n"\
                "<button class=\"btn\" id=\"mode_out\" onclick=SetInOutMode(2)>out</button>\n"\
                "</div>\n"\
                "<div id=\"mode_in_out_time_bt\"></div>\n"\
               "</div>\n"\
          "<div id=\"vocation\">\n"\
            "<input type=\"checkbox\" id=\"isVacationSet\">vocation<br>\n"\
          "</div>\n"\
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
    "</body>\n"\
"</html>\n"\
};
const char* _frontend_term_main_js_ PROGMEM ={
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
            "document.getElementById(\"air_term\").innerHTML=res[\"air_term\"].toFixed(2);\n"\
            "document.getElementById(\"air_humm\").innerHTML=res[\"air_humm\"];\n"\
            "document.getElementById(\"floor_term\").innerHTML=res[\"floor_term\"].toFixed(2);\n"\
            "document.getElementById(\"time_status\").innerHTML=res[\"time_status\"];\n"\
            "document.getElementById(\"desired_temperature\").innerHTML=res[\"desired_temperature\"];\n"\
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
"var in_out_mode=0;\n"\
"function SetInOutMode(mode,val){\n"\
    "let node = document.getElementById(\"mode_in_out_time_bt\");\n"\
    "if(mode==in_out_mode){\n"\
        "mode=0;\n"\
    "}\n"\
    "in_out_mode=mode;\n"\
    "document.getElementById(\"mode_in\").style.backgroundColor = (1==mode)?colorSelection:document.body.style.backgroundColor;\n"\
    "document.getElementById(\"mode_out\").style.backgroundColor = (2==mode)?colorSelection:document.body.style.backgroundColor;\n"\
"}\n"\
\
"function createInOutMode(){\n"\
    "let node = document.getElementById(\"mode_in_out_time_bt\");\n"\
    "for(let x=1;x!=9;x++){\n"\
         "let button=document.createElement(\"button\")\n"\
            "button.innerHTML = x;\n"\
         "button.setAttribute(\"id\", \"button_in_out_\"+x);\n"\
            "button.setAttribute(\"class\", \"button\");\n"\
           "button.setAttribute(\"onclick\", \"in_out_time_bt_click(\"+x+\")\");\n"\
        "node.appendChild(button);\n"\
        "}\n"\
    "SetInOutMode(0,0);\n"\
"}\n"\
"var InOut_Shift=0;\n"\
"function in_out_time_bt_click(shift){\n"\
    "if(InOut_Shift==shift){\n"\
        "shift=0;\n"\
    "}\n"\
    "console.log(\"bt_click \"+shift);\n"\
    "InOut_Shift=shift;\n"\
    "for(let x=1;x!=9;x++){\n"\
         "document.getElementById(\"button_in_out_\"+x).style.backgroundColor = (x==shift)?colorSelection:document.body.style.backgroundColor;\n"\
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
          "SetInOutMode(res[\"in_out_mode\"],res[\"in_out_mode_value\"]);\n"\
          "document.getElementById(\"term_vacation\").value=res[\"term_vacation\"];\n"\
          "document.getElementById(\"term_night\").value=res[\"term_night\"];\n"\
          "document.getElementById(\"term_day\").value=res[\"term_day\"];\n"\
          "document.getElementById(\"term_max\").innerHTML=res[\"term_max\"];\n"\
          "document.getElementById(\"control_is_on\").checked=res[\"isOn\"];\n"\
          "document.getElementById(\"isVacationSet\").checked=res[\"isVacationSet\"] ;\n"\
\
"//          root[\"is_err_cooling\"] = is_err_cooling_;\n"\
"//          root[\"term_err_cooling\"] = term_err_cooling_;\n"\
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
\
    "myJSON[\"isOn\"]=document.getElementById(\"control_is_on\").checked;\n"\
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
    "createInOutMode();\n"\
    "MainConfigLoad();\n"\
    "PresetLoad();\n"\
    "StatusLoad();\n"\
    "setInterval(\'StatusLoad()\', 5000);\n"\
"}\n"\
};
const char* _frontend_WiFiConfigEntry_html_ PROGMEM ={
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
const char *_frontend_favicon_ico_ PROGMEM ={"\x00\x00\x01\x00\x01\x00\x10\x10\x00\x00\x01\x00\x20\x00\x68\x04\x00\x00\x16\x00\x00\x00\x28\x00\x00\x00\x10\x00\x00\x00\x20\x00\x00\x00\x01\x00\x20\x00\x00\x00\x00\x00\x00\x04\x00\x00\x12\x0b\x00\x00\x12\x0b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x25\x49\x00\x00\x0b\x15\x46\x00\x22\x41\xae\x00\x2d\x50\xb3\x00\x31\x4f\xb2\x00\x35\x4e\xb2\x00\x3a\x4d\xb2\x00\x3e\x4d\xb2\x00\x40\x4d\xb2\x00\x3c\x4d\xb2\x00\x37\x4e\xb2\x00\x32\x4e\xb2\x00\x2d\x4f\xb3\x00\x23\x41\xae\x00\x0b\x15\x46\x00\x25\x49\x00\x01\x8f\xff\x00\x00\x18\x31\x6f\x10\x5b\x9f\xfb\x18\x74\xc0\xff\x11\x7c\xcc\xff\x15\x8c\xd9\xff\x02\x8d\xe2\xff\x00\x8f\xe1\xff\x00\x92\xe1\xff\x02\x8e\xe1\xff\x17\x90\xdd\xff\x22\x8e\xdb\xff\x20\x87\xdd\xff\x0b\x61\xb1\xfb\x00\x18\x2f\x6f\x00\x91\xff\x00\x00\x1b\x3d\x00\x00\x07\x1c\x42\x43\x60\x87\xea\xa0\xb7\xd0\xff\x77\x97\xb9\xff\x46\x7b\xae\xff\x05\x7c\xdd\xff\x00\x88\xfd\xff\x00\x89\xff\xff\x0a\x90\xfe\xff\x91\xc3\xef\xff\xd1\xdb\xe7\xff\xc4\xd4\xe5\xff\x49\x69\x94\xea\x00\x06\x1a\x42\x00\x1b\x3d\x00\x00\x00\x05\x00\x00\x00\x00\x18\x63\x64\x69\xc8\xcf\xda\xe7\xff\x74\x8b\xdd\xff\x10\x39\xbf\xff\x00\x3a\xa0\xff\x00\x6f\xc0\xff\x00\x94\xf5\xff\x0c\x9f\xfe\xff\xad\xd7\xf3\xff\xf8\xf3\xee\xff\xe8\xe6\xe4\xff\x65\x65\x69\xc8\x00\x00\x00\x18\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x13\x6e\x6d\x6a\xbf\xc1\xca\xe3\xff\x25\x43\xd3\xff\x00\x20\xcc\xff\x00\x2b\xc4\xff\x00\x39\x99\xff\x00\x6c\xac\xff\x0d\x97\xe5\xff\xb0\xdd\xf8\xff\xfc\xf9\xf6\xff\xeb\xea\xe9\xff\x6c\x6b\x6a\xbf\x00\x00\x00\x13\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x12\x6f\x6e\x6d\xbe\xe2\xe2\xeb\xff\x6f\x7f\xe0\xff\x07\x2b\xce\xff\x00\x2b\xd0\xff\x00\x2e\xc3\xff\x00\x40\x9d\xff\x0b\x74\xa7\xff\xa1\xc7\xd8\xff\xfa\xf8\xf6\xff\xef\xef\xee\xff\x6e\x6d\x6d\xbe\x00\x00\x00\x12\x00\x00\x00\x00\x00\x05\x0a\x19\x00\x00\x04\x5b\x66\x65\x65\xcf\xf3\xf2\xf1\xff\xed\xed\xf9\xff\x66\x7c\xde\xff\x02\x2f\xcf\xff\x00\x35\xd4\xff\x00\x31\xc2\xff\x08\x4a\xa5\xff\x82\x9f\xb0\xff\xd7\xd5\xd3\xff\xe5\xe5\xe4\xff\x65\x65\x65\xcf\x00\x00\x04\x5b\x00\x06\x0a\x19\x00\x1a\x30\x83\x00\x44\x7d\xf1\x54\x6f\x83\xfa\xf5\xf4\xf3\xff\xff\xff\xff\xff\xb1\xe5\xf9\xff\x0d\x6d\xdc\xff\x00\x32\xcf\xff\x00\x3e\xd9\xff\x03\x32\xbf\xff\x59\x67\xac\xff\xbd\xbd\xc2\xff\xd2\xd1\xcf\xff\x4c\x67\x7b\xfa\x00\x43\x7d\xf1\x00\x19\x30\x83\x00\x14\x27\x68\x00\x5e\xad\xf2\x25\x98\xec\xff\xb8\xdb\xf7\xff\xfe\xfd\xfe\xff\xdc\xfa\xff\xff\x8b\xda\xfa\xff\x57\x77\xda\xff\x09\x37\xcf\xff\x00\x46\xdc\xff\x0c\x36\xbc\xff\x78\x7b\xb4\xff\x9b\xb6\xcd\xff\x20\x85\xdc\xff\x00\x4e\xae\xf3\x00\x10\x29\x6a\x00\x00\x00\x18\x00\x2e\x5b\xaf\x00\x73\xd4\xff\x25\xa6\xfd\xff\xa7\xd6\xfa\xff\xf9\xfa\xfe\xff\xff\xff\xff\xff\xeb\xec\xf9\xff\x6d\x7a\xd6\xff\x07\x39\xcd\xff\x30\x6c\xde\xff\x99\x9d\xbd\xff\x7b\x9c\xb3\xff\x12\x5f\xc5\xff\x00\x21\x63\xb4\x00\x00\x00\x1b\x00\x23\x45\x00\x00\x03\x06\x2a\x00\x2d\x5b\xb2\x00\x6f\xcc\xfc\x19\xa7\xfc\xff\x92\xd0\xfa\xff\xf4\xf7\xfd\xff\xff\xff\xff\xff\xec\xec\xf9\xff\x78\x80\xcf\xff\x9d\xa3\xc5\xff\xe4\xe0\xdb\xff\xb8\xa0\xc0\xff\x4f\x38\x79\xf7\x08\x05\x17\x6b\x00\x00\x00\x01\x00\x00\x00\x00\x00\x15\x2b\x00\x00\x00\x00\x20\x00\x2a\x51\xa2\x00\x73\xc1\xfa\x10\xb0\xfb\xff\x7c\xcc\xf9\xff\xee\xf2\xfd\xff\xee\xf3\xfe\xff\x80\xc2\xec\xff\x84\xa9\xb7\xff\xbe\xa1\xc5\xff\x91\x2e\xd4\xff\x68\x02\xae\xff\x34\x00\x57\xd0\x08\x00\x0e\x3e\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\x13\x00\x00\x00\x00\x17\x00\x2c\x48\x93\x00\x7b\xb8\xf6\x0a\xba\xfa\xff\x60\xc7\xf9\xff\x60\xc6\xf9\xff\x09\xb2\xfa\xff\x1d\x76\xaf\xf9\x61\x39\x81\xf5\x71\x02\xbf\xff\x7f\x00\xd9\xff\x62\x00\xa7\xfb\x19\x00\x2a\x8b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x0b\x00\x00\x00\x00\x11\x00\x2c\x3f\x85\x00\x81\xac\xf1\x02\xc9\xf9\xff\x02\xc2\xf9\xff\x00\x77\xae\xf2\x00\x28\x43\x89\x14\x03\x1d\x6c\x40\x00\x6d\xe5\x66\x00\xad\xff\x48\x00\x7b\xdf\x0f\x00\x1a\x50\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x06\x00\x00\x00\x00\x0c\x00\x2a\x35\x75\x00\x7f\x9c\xec\x00\x79\x9d\xec\x00\x26\x36\x77\x00\x00\x00\x0d\x00\x00\x00\x05\x0e\x00\x18\x4f\x19\x00\x2c\x8b\x10\x00\x1b\x4c\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x09\x00\x19\x1d\x69\x00\x18\x1d\x6a\x00\x00\x00\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x80\x01\x00\x00\x80\x01\x00\x00\x80\x01\x00\x00\x80\x01\x00\x00\x80\x01\x00\x00\x80\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\xc0\x00\x00\x00\xe0\x00\x00\x00\xf0\x00\x00\x00\xf8\x00\x00\x00\xfc\x3b\x00\x00"};
const auto _frontend_favicon_ico_SZ=1150;

//converted list
//  CFrontendFS::add(server, "/def_preset.json", ct_json,_frontend_def_preset_json_);
//  CFrontendFS::add(server, "/def_termistor.json", ct_json,_frontend_def_termistor_json_);
//  CFrontendFS::add(server, "/term_main.css", ct_css,_frontend_term_main_css_);
//  CFrontendFS::add(server, "/term_main.html", ct_html,_frontend_term_main_html_);
//  CFrontendFS::add(server, "/term_main.js", ct_js,_frontend_term_main_js_);
//  CFrontendFS::add(server, "/WiFiConfigEntry.html", ct_html,_frontend_WiFiConfigEntry_html_);
//  CFrontendFS::add(server, "/favicon.ico", ct_ico,_frontend_favicon_ico_);
#endif
//EOF
