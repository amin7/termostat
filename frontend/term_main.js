let dayOfWeekStr=["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"];
const colorSelected="#fc6400";
const colorSelection="#fc0000";
const colorNotSelected="#00a3fc";        	
const colorNotSelection="#0800fc";

let heat_mode_ids=["mode_off","mode_schedule","mode_vocation","mode_in","mode_out"];
	
xmlHttp=createXmlHttpObject();

  function createXmlHttpObject(){
    if(window.XMLHttpRequest){
      xmlHttp=new XMLHttpRequest();
    }else{
      xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
    }
    return xmlHttp;
  }
  
  function PresetLoad(){
	  let presetsList = document.getElementById("PresetsList");
	    while (presetsList.firstChild) {
	    	presetsList.removeChild(presetsList.firstChild);
	      }
	  
      var xh = new XMLHttpRequest();
      xh.onreadystatechange = function(){
        if (xh.readyState == 4){
          if(xh.status == 200) {
            var res = JSON.parse(xh.responseText);
            console.log(res);
            add_Presets(res);
          }
        }
      };
      xh.open("GET", "/ConfigLoad?name=presets", true);
      xh.send(null);
	}

  function StatusLoad(){
      var xh = new XMLHttpRequest();
      xh.onreadystatechange = function(){
        if (xh.readyState == 4){
          if(xh.status == 200) {
            var res = JSON.parse(xh.responseText);
            console.log(res);
            document.getElementById("air_term").innerHTML=res["air_term"].toFixed(2);
            document.getElementById("air_humm").innerHTML=res["air_humm"];
            document.getElementById("floor_term").innerHTML=res["floor_term"].toFixed(2);
            document.getElementById("time_status").innerHTML=res["time_status"];
            document.getElementById("desired_temperature").innerHTML=res["desired_temperature"];
            updateCurrDateTime(res["time"]*1000);
            document.getElementById("heater_on").innerHTML=res["heater_on"];
          }
        }
      };
      xh.open("GET", "/ConfigLoad?name=status", true);
      xh.send(null);
    }
    
function PresetSave(){
  if(xmlHttp.readyState==0||xmlHttp.readyState==4){
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
		  console.log("saved ok");
	  }
	}
	let myJSON = new Object;	
	myJSON.Presets=[];
	var doc = document.getElementById("PresetsList");
	for (i = 0; i < doc.children.length; i++) {
		let preset = new Object;	
		preset.weekDay=doc.children[i].preset.weekDay.getValue();
		preset.hours=doc.children[i].preset.hours.getValue();
		myJSON.Presets.push(preset);
	}	
    var data = JSON.stringify(myJSON);
	xmlHttp.open('PUT',"/ConfigSave?name=presets",true); 
	xmlHttp.setRequestHeader("Content-Type", "application/json");				
	xmlHttp.send(data);
	console.log(data);	
  }
}

var in_out_mode=0;
function SetInOutMode(mode,val){
	let node = document.getElementById("mode_in_out_time_bt");	
	if(mode==in_out_mode){
		mode=0;				
	}	
	in_out_mode=mode;	
	document.getElementById("mode_in").style.backgroundColor = (1==mode)?colorSelection:document.body.style.backgroundColor;
	document.getElementById("mode_out").style.backgroundColor = (2==mode)?colorSelection:document.body.style.backgroundColor;
}

function createInOutMode(){
	let node = document.getElementById("mode_in_out_time_bt");
	for(let x=1;x!=9;x++){
		 let button=document.createElement("button")
	   	 button.innerHTML = x;
		 button.setAttribute("id", "button_in_out_"+x);
	   	 button.setAttribute("class", "button");
	   	button.setAttribute("onclick", "in_out_time_bt_click("+x+")");	   	
	    node.appendChild(button);
		}
	SetInOutMode(0,0);
}
var InOut_Shift=0;
function in_out_time_bt_click(shift){
	if(InOut_Shift==shift){
		shift=0;
	}
	console.log("bt_click "+shift);	
	InOut_Shift=shift;
	for(let x=1;x!=9;x++){		 
		 document.getElementById("button_in_out_"+x).style.backgroundColor = (x==shift)?colorSelection:document.body.style.backgroundColor;
	}
}


function MainConfigLoad(){
    var xh = new XMLHttpRequest();
    xh.onreadystatechange = function(){
      if (xh.readyState == 4){
        if(xh.status == 200) {
          var res = JSON.parse(xh.responseText);
          console.log(res);
          SetInOutMode(res["in_out_mode"],res["in_out_mode_value"]);
          document.getElementById("term_vacation").value=res["term_vacation"];
          document.getElementById("term_night").value=res["term_night"];
          document.getElementById("term_day").value=res["term_day"];
          document.getElementById("term_max").innerHTML=res["term_max"];
          document.getElementById("control_is_on").checked=res["isOn"];
          document.getElementById("isVacationSet").checked=res["isVacationSet"] ;
          
//          root["is_err_cooling"] = is_err_cooling_;
//          root["term_err_cooling"] = term_err_cooling_;
        }
      }
    };
    xh.open("GET", "/ConfigLoad?name=mainconfig", true);
    xh.send(null);
  }

function MainConfigSave(){
if(xmlHttp.readyState==0||xmlHttp.readyState==4){
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
		  console.log("saved ok");
	  }
	}
	let myJSON = new Object;	
	
	myJSON["isOn"]=document.getElementById("control_is_on").checked;
	myJSON["heat_mode"]=heat_mode;
	myJSON["term_vacation"]=document.getElementById("term_vacation").value;
	myJSON["term_night"]=document.getElementById("term_night").value;
	myJSON["term_day"]=document.getElementById("term_day").value;
	
	var data = JSON.stringify(myJSON);
	xmlHttp.open('PUT',"/ConfigSave?name=mainconfig",true); 
	xmlHttp.setRequestHeader("Content-Type", "application/json");				
	xmlHttp.send(data);
	console.log(data);	
	MainConfigLoad(); //loopback
}
}
      
function selectionList(parent,valList,initial){	
    var isPressed=false;
    var isSelected=false;
    var selBeg,selEnd;
    let myNode =document.createElement("div");
    parent.appendChild(myNode);
    if(myNode==null)
    	return;
    this.getValue= function() {
    	let bitmap=0;
    	for (var index in myNode.childNodes) {    	
    		if(myNode.childNodes[index].value=="true"){
    			bitmap+=(1<<index);
    		}
       	}
    	return bitmap;
    }
    function dispaySelection(selBeg,selEnd,isSelected){	        	
    	childNodes=myNode.childNodes;
        i = childNodes.length;

        while (i--) {
            if (childNodes[i].getAttribute("class") == "button") {
            	var button=childNodes[i];	                	
            	var cur=parseInt(button.name);
            	if((cur>=selBeg)&&(cur<=selEnd)){	                		
            		button.style.backgroundColor = isSelected?colorSelection:colorNotSelection;
            	}else{ //show default state
            		button.style.backgroundColor = (button.value=="true")?colorSelected:colorNotSelected;
            	}
            	
            }
        }
    }	  
   	 this.doSelection= function(selBeg,selEnd,isSelected){	 		 	
     	childNodes=myNode.childNodes
         i = childNodes.length;                    
         while (i--) {    
         	var button=childNodes[i];                    	
         	var cur=parseInt(button.name);
        	if((cur>=selBeg)&&(cur<=selEnd))
        		button.value=isSelected;
        	button.style.backgroundColor = (button.value=="true")?colorSelected:colorNotSelected;
         }	         		 
 		}
    this.moveState=function(button) {
    	if(isPressed){        		
    		selEnd=parseInt(button.name);
    		if(selBeg<=selEnd)
    			dispaySelection(selBeg,selEnd,isSelected);
    		else
    			dispaySelection(selEnd,selBeg,isSelected);
    	}	        	
    }			
    this.keyDown=function (button) {
    	 isPressed=true;        	         	 
         if (button.value == 'false') {
       	  isSelected=true;
         }
         else {            	  
       	  isSelected=false;
         }
         selBeg=selEnd=parseInt(button.name);
         dispaySelection(selBeg,selEnd,isSelected);
   	};
    this.keyUp=function () {
    	 if(isPressed){
			 if(selBeg<=selEnd)
			   this.doSelection(selBeg,selEnd,isSelected);
			 else
				 this.doSelection(selEnd,selBeg,isSelected);
		 }
		 isPressed=false;
    };
    
    var obj = this;
   	for(var i=0;i<valList.length;i++)
   	{
   		let isSet=initial&(1<<i)?true:false;
       	 let button=document.createElement("button")
       	 button.innerHTML = valList[i];
       	 button.setAttribute("name", i);
       	 button.setAttribute("class", "button");
       	 button.setAttribute("id", "button_schedule_hour");
       	
       	 button.addEventListener("mousedown", function(){ obj.keyDown(button); });
         button.addEventListener("mouseenter", function(){ obj.moveState(button);});
         
         button.value=isSet;         
         button.style.backgroundColor = (button.value=="true")?colorSelected:colorNotSelected;               
       	 myNode.appendChild(button);
   	}		   	 		   		
   	window.addEventListener('mouseup', function(event){obj.keyUp();});   	
}
function updateCurrDateTime(timestamt){
	var options = {  
		    weekday: "long", year: "numeric", month: "short",  
		    day: "numeric", hour: "2-digit", minute: "2-digit",hour12: false  
		};  
	var date=new Date(timestamt);
	document.getElementById("time").innerHTML = date.toUTCString([], options);
}
function htmlObj(html){
	let el = document.createElement("span");
	el.innerHTML = html;
	return el;
}

function preset(placement,initVal){
	let div=document.createElement("div");		
	this.weekDay=new selectionList(div,dayOfWeekStr,initVal.weekDay);
	div.appendChild(document.createElement("BR"));
	var valArray=[24];	
	for(var i=0;i<24;i++){
		valArray[i]=""+i;
	}		
	this.hours= new selectionList(div,valArray,initVal.hours);
	div.appendChild(document.createElement("BR"));
	placement.appendChild(div);
}

function add_Presets(config){	
	let presetsList = document.getElementById("PresetsList");
	for (var key in config.Presets) {
		let listItem=document.createElement("LI");		
		listItem.preset =new preset(listItem,config.Presets[key]);
		listItem.appendChild(document.createElement("BR"));
		presetsList.appendChild(listItem);	
	}
}

function init(){	
	createInOutMode();
	MainConfigLoad();
	PresetLoad();
	StatusLoad();
	setInterval('StatusLoad()', 5000);
}    	