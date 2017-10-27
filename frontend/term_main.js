function dayOfWeekAsString(dayIndex) {
  return ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"][dayIndex];
}
function daySchedule(parent){
	const colorSelected="#fc6400";
	const colorSelection="#fc0000";
	const colorNotSelected="#00a3fc";        	
	const colorNotSelection="#0800fc";
    var isPressed=false;
    var isSelected=false;
    var selBeg,selEnd;
    let myNode = parent;
    if(myNode==null)
    	return;
	this.setVal=function(val){
		
	}
	this.getVal=function(){
		return 128;        		
	}
    function dispaySelection(selBeg,selEnd,isSelected){	        	
    	childNodes=myNode.childNodes;
        i = childNodes.length;

        while (i--) {
            if (childNodes[i].getAttribute("class") == "button") {
            	var button=childNodes[i];	                	
            	var cur=parseInt(button.innerHTML);
            	if((cur>=selBeg)&&(cur<=selEnd)){	                		
            		button.style.backgroundColor = isSelected?colorSelection:colorNotSelection;
            	}else{ //show default state
            		button.style.backgroundColor = (button.value=="true")?colorSelected:colorNotSelected;
            	}
            	
            }
        }
    }	    
   	 function doSelection(selBeg,selEnd,isSelected){	 		 	
     	childNodes=myNode.childNodes
         i = childNodes.length;                    
         while (i--) {    
         	var button=childNodes[i];                    	
         	var cur=parseInt(button.innerHTML);
        	if((cur>=selBeg)&&(cur<=selEnd))
        		button.value=isSelected;
        	button.style.backgroundColor = (button.value=="true")?colorSelected:colorNotSelected;
         }	         		 
 		}
    this.moveState=function(button) {
    	if(isPressed){        		
    		selEnd=parseInt(button.innerHTML);;
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
         selBeg=selEnd=parseInt(button.innerHTML);;
         dispaySelection(selBeg,selEnd,isSelected);
   	};
    this.keyUp=function () {
    	 if(isPressed){
			 if(selBeg<=selEnd)
			   doSelection(selBeg,selEnd,isSelected);
			 else
			   doSelection(selEnd,selBeg,isSelected);
		 }
		 isPressed=false;
    };
    
    var obj = this;
   	for(var i=0;i<24;i++){
       	 let button=document.createElement("button")
       	 button.innerHTML = i;
       	 button.setAttribute("class", "button");
       	 button.addEventListener("mousedown", function(){ obj.keyDown(button); });
         button.addEventListener("mouseenter", function(){ obj.moveState(button);});
       	 button.value= false;
       	 myNode.appendChild(button);
   	}		   	 		   		
   	window.addEventListener('mouseup', function(event){obj.keyUp();});   	
}

function init(){
	let myNode = document.getElementById("weekSchedule");
	for(let i=0;i<7;i++){
		let item=document.createElement("DIV")
		let weekday=document.createTextNode(dayOfWeekAsString(i));
		myNode.appendChild(weekday);
		new daySchedule(item);
		myNode.appendChild(item);
		let br=document.createElement("BR")
		myNode.appendChild(br);
		br=document.createElement("BR")
		myNode.appendChild(br);
	}	
}    	