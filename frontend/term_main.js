let dayOfWeekStr=["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"];

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
      
function selectionList(parent,valList,initial){	
	const colorSelected="#fc6400";
	const colorSelection="#fc0000";
	const colorNotSelected="#00a3fc";        	
	const colorNotSelection="#0800fc";
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
function updateCurrDateTime(){
	var options = {  
		    weekday: "long", year: "numeric", month: "short",  
		    day: "numeric", hour: "2-digit", minute: "2-digit",hour12: false  
		};  
	var date=new Date();
	document.getElementById("date").innerHTML = date.toLocaleTimeString([], options);
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
	updateCurrDateTime();
	setInterval('updateCurrDateTime()', 1000);
//	let val=new Object;
//	val={
//			  "Presets": [
//				    {
//				      "weekDay": 1,
//				      "hours": 2
//				    },
//				    {
//				      "weekDay": 3,
//				      "hours": 0
//				    }
//				  ]
//				}
//	add_Presets(val);//for test
	PresetLoad();
}    	