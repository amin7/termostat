let dayOfWeekStr=["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"];
const colorSelected="#fc6400";
const colorSelection="#fc0000";
const colorNotSelected="#00a3fc";        	
const colorNotSelection="#0800fc";
  
  function PresetLoad(){  
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function(){
    if (xmlHttp.readyState == 4){
      if(xmlHttp.status == 200) {
    	  let presetsList = document.getElementById("PresetsList");
  	    while (presetsList.firstChild) {
  	    	presetsList.removeChild(presetsList.firstChild);
  	      }
        var res = JSON.parse(xmlHttp.responseText);
        console.log(res);
        add_Presets(res);
      }
    }
  };
  xmlHttp.open("GET", "/ConfigLoad?name=presets", true);
  xmlHttp.send(null);
}

function SinkTime(){
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
		  console.log("SinkTime ok");
		  }
	  }
	let myJSON = new Object;	
	var curdate = new Date();
	myJSON.time=curdate.getTime()/1000;
	var data = JSON.stringify(myJSON);
	xmlHttp.open('PUT',"/ConfigSave?name=status",true); 
	xmlHttp.setRequestHeader("Content-Type", "application/json");				
	xmlHttp.send(data);
	console.log(data);	  
}

  function StatusLoad(){
	  var xmlHttp = new XMLHttpRequest();
	  xmlHttp.onreadystatechange = function(){
    if (xmlHttp.readyState == 4){
      if(xmlHttp.status == 200) {
        var res = JSON.parse(xmlHttp.responseText);
        console.log(res);
        document.getElementById("air_term").innerHTML=res["air_term"].toFixed(2);
        document.getElementById("air_humm").innerHTML=res["air_humm"];
        document.getElementById("floor_term").innerHTML=res["floor_term"].toFixed(2);
        document.getElementById("time_status").innerHTML=res["time_status"];
        document.getElementById("desired_temperature").innerHTML=res["desired_temperature"];
        updateCurrDateTime(res["time"]*1000);
        document.getElementById("heater_on").innerHTML=res["heater_on"];
        if(2!=res["time_status"]){
        	SinkTime();
        }
      }
    }
  };
  xmlHttp.open("GET", "/ConfigLoad?name=status", true);
  xmlHttp.send(null);
  }
    
function PresetSave(){
	var xmlHttp = new XMLHttpRequest();
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

function createInOutMode(node_id){
	let node = document.getElementById(node_id);
	while (node.firstChild) {
		node.removeChild(node.firstChild);
      }
	var curdate = new Date();	
	for(let x=-1;x!=9;x++){	
		 let button=document.createElement("button")	;	 
		 if(-1!=x){
			 var tmpdate = new Date(curdate.getFullYear(),curdate.getMonth()
					 ,curdate.getDate(),curdate.getHours()+x,0,0);
			 button.innerHTML = tmpdate.getHours()+":00";
		     button.value= tmpdate.getTime();
		     button.mode=node_id;
		     
		 }else{
			 button.innerHTML = "off";
			 button.value= 0;
		 }
	   	 button.setAttribute("class", "button");
	   	 button.setAttribute("onclick", "in_out_time_bt_click(this)");	   	
	    node.appendChild(button);
		}
}
var selected_InOut=0;
function in_out_time_bt_click(button){
	let node = document.getElementById("mode_in");
	node.childNodes.forEach(function(element){
		element.style.backgroundColor=document.body.style.backgroundColor;
	});
	node = document.getElementById("mode_out");
	node.childNodes.forEach(function(element){
		element.style.backgroundColor=document.body.style.backgroundColor;
	});
	selected_InOut=0;	
	if(button.value!="0"){
		in_out_time_bt_set(button.mode,button.value);
	}
}
function in_out_time_bt_set(node_id,time){
	selected_InOut=0;
	let node = document.getElementById(node_id);
	node.childNodes.forEach(function(element){
		if(element.value<=time
				&& element.value!=0){
			element.style.backgroundColor = node_id=="mode_in"?colorSelected:colorNotSelected;
			selected_InOut=element;	
			return;
		}
	});
}
function setVacationDate(id,date){
	var inp=document.getElementById(id);
	if(date){
		inp.valueAsDate=new Date(date*1000)
	}else{
		inp.value="";
	}
}
function MainConfigLoad(){
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
      var res = JSON.parse(xmlHttp.responseText);
      console.log(res);
      document.getElementById("term_vacation").value=res["term_vacation"];
      document.getElementById("term_night").value=res["term_night"];
      document.getElementById("term_day").value=res["term_day"];
      document.getElementById("term_max").innerHTML=res["term_max"];
      document.getElementById("control_is_on").checked=res["isOn"];
      document.getElementById("isVacationSet").checked=res["isVacationSet"] ;
		createInOutMode("mode_in");
		createInOutMode("mode_out");
		selected_InOut=0
		if(res.hasOwnProperty("mode_in")){
			in_out_time_bt_set("mode_in",res["mode_in"]*1000);
		}
		if(res.hasOwnProperty("mode_out")){
			in_out_time_bt_set("mode_out",res["mode_out"]*1000);
		}

		let vocation_start=res["vocation_start"];
		let vocation_end=res["vocation_end"];
		setVacationDate("vocation_start",vocation_start);
		setVacationDate("vocation_end",vocation_end);
		
		document.getElementById("isVacationSet").checked=vocation_start||vocation_end;		
		vacation_show(vocation_start||vocation_end);
		
    }
  };
  xmlHttp.open("GET", "/ConfigLoad?name=mainconfig", true);
  xmlHttp.send(null);
 
}

function MainConfigSave(){
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
		  console.log("saved ok");
	  }
	}
	let myJSON = new Object;	
	
	myJSON["isOn"]=document.getElementById("control_is_on").checked;
	myJSON["term_vacation"]=document.getElementById("term_vacation").value;
	myJSON["term_night"]=document.getElementById("term_night").value;
	myJSON["term_day"]=document.getElementById("term_day").value;
	if(selected_InOut){
		myJSON[selected_InOut.mode]=selected_InOut.value/1000;//in sec ardujson limitation		
	}
	if(document.getElementById("isVacationSet").checked){		
		myJSON["vocation_start"]=document.getElementById("vocation_start").valueAsDate/1000;
		myJSON["vocation_end"]=document.getElementById("vocation_end").valueAsDate/1000;
	}else{
		myJSON["vocation_start"]=0;
		myJSON["vocation_end"]=0;
	}
	
	var data = JSON.stringify(myJSON);
	xmlHttp.open('PUT',"/ConfigSave?name=mainconfig",true); 
	xmlHttp.setRequestHeader("Content-Type", "application/json");
	
	xmlHttp.send(data);
	console.log(data);	
	MainConfigLoad(); //loopback
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
	document.getElementById("time").innerHTML = date.toString([], options);
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


function RegulatorLoad(){
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
      var res = JSON.parse(xmlHttp.responseText);
      console.log(res);
      document.getElementById("isRegulatorOn").checked=res["mode"];
      document.getElementById("term_regulator").value=res["setpoint"];
      document.getElementById("term_hysteresis").value=res["hysteresis"];
    }
  };
  xmlHttp.open("GET", "/ConfigLoad?name=regulator", true);
  xmlHttp.send(null);
}

function RegulatorSave(){
	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange=function(){
	  if(xmlHttp.readyState==4&&xmlHttp.status==200){  
		  console.log("saved ok");
	  }
	}
	let myJSON = new Object;	
	
	myJSON["mode"]=document.getElementById("isRegulatorOn").checked;
	myJSON["setpoint"]=document.getElementById("term_regulator").value;
	myJSON["hysteresis"]=document.getElementById("term_hysteresis").value;
	
	var data = JSON.stringify(myJSON);
	xmlHttp.open('PUT',"/ConfigSave?name=regulator",true); 
	xmlHttp.setRequestHeader("Content-Type", "application/json");
	
	xmlHttp.send(data);
	console.log(data);	
}

function vacation_show(bshow) {
    var x = document.getElementById("vocation_date");
    if (bshow) {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
}

function init(){	
	vacation_show(false);
	createInOutMode("mode_in");
	createInOutMode("mode_out");
	selected_InOut=0
	MainConfigLoad();
	PresetLoad();
	StatusLoad();
	RegulatorLoad();	
	setInterval('StatusLoad()', 5000);
}    	