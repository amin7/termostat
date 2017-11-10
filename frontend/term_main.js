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
function saveSchedule(){
  if(xmlHttp.readyState==0||xmlHttp.readyState==4){
	    xmlHttp.onreadystatechange=function(){
	      if(xmlHttp.readyState==4&&xmlHttp.status==200){  
	    	  console.log("saved ok");
	      }
	    }
	var doc = document.getElementById("PresetsList");
	let myJSON=null;
	if(doc.children.length){
		let obj=doc.children[0].controlData;
		myJSON = JSON.stringify(obj);
	}
	 var url = "PresetAdd?data=" + encodeURIComponent(myJSON);
			 
	 xmlHttp.open('GET',url,true); //POST is more safely but ... harder to suuport from esp side
	 xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");				
	 console.log(url);
	 xmlHttp.send(null);
  }
}
	      
function selectionList(parent,valList){
	this.Value=[];
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
        	this.Value[i]=button.value=="true";
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
   	for(var i=0;i<valList.length;i++){
   		 this.Value.push(false);
       	 let button=document.createElement("button")
       	 button.innerHTML = valList[i];
       	 button.setAttribute("name", i);
       	 button.setAttribute("class", "button");
       	 button.setAttribute("id", "button_schedule_hour");
       	
       	 button.addEventListener("mousedown", function(){ obj.keyDown(button); });
         button.addEventListener("mouseenter", function(){ obj.moveState(button);});
       	 button.value= false;
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
function presetControl(placement,payload){	

	//<active><up>><down><clone><delete> <payload>
	let myNode = placement;
	let main=document.createElement("div");
	let obj=this;
	
	this.isActive=false;
	
	let input = document.createElement("INPUT");
	input.setAttribute("type", "checkbox");
	input.addEventListener("change", function(){obj.isActive=input.checked;	});
	main.appendChild(input);
	
	main.appendChild(htmlObj('<button >Up</button>'+
	'<button >Down</button>'+
	'<button >clone</button>'))
	var bdel = document.createElement("button");
	bdel.innerHTML="delete";
	bdel.type= "button";
	bdel.addEventListener("mousedown", function(){ myNode.parentNode.removeChild(myNode); });
	main.appendChild(bdel);
	myNode.appendChild(main);
	this.data=new payload(placement);
	
}


function byWeekday(placement){			 		
	this.type="WeekDay";
	this.weekDay=new selectionList(placement,dayOfWeekStr);
	placement.appendChild(document.createElement("BR"));
	var valArray=[24];
	for(var i=0;i<24;i++){
		valArray[i]=""+i;
	}	
	this.hours= new selectionList(placement,valArray);
	placement.appendChild(document.createElement("BR"));
}

function add_byWeekday(){
	let presetsList = document.getElementById("PresetsList");
	let listItem=document.createElement("LI");
	listItem.controlData =new presetControl(listItem,byWeekday);
	presetsList.insertBefore(listItem,presetsList.childNodes[0]);	
}

function listSerialize(){
	var cache = [];
	var doc = document.getElementById("PresetsList");
	for (i = 0; i < doc.children.length; i++) {
		let obj=doc.children[i].controlData;
		let myJSON = JSON.stringify(obj);
		
		cache.push(myJSON);
	}
	console.log(cache);
	
	
}

function init(){
	updateCurrDateTime();
	setInterval('updateCurrDateTime()', 1000);	
	add_byWeekday();//for test
	
}    	