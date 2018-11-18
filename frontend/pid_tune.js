var set_pid_mode;
function PidStatusLoad(){
      var xh = new XMLHttpRequest();
      xh.onreadystatechange = function(){
        if (xh.readyState == 4){
          if(xh.status == 200) {
            var res = JSON.parse(xh.responseText);
            console.log(res); 
          document.getElementById("pid_mode").innerHTML=res["mode"];
          }
          var pretty = JSON.stringify(res, undefined, 4);
          document.getElementById('myTextArea').value = pretty;
        }
      };
      xh.open("GET", "/ConfigLoad?name=PID_tune", true);
      xh.send(null);
    }
 
function SetMode(mode){
	set_pid_mode=mode;
	PidStatusSave()
 }
 function PidStatusSave(){
	 var xh = new XMLHttpRequest();
	  if(xh.readyState==0||xh.readyState==4){
		  xh.onreadystatechange=function(){
		  if(xh.readyState==4&&xh.status==200){  
			  console.log("saved ok");
		  }
		}
		let myJSON = new Object;	
		myJSON["mode"]=set_pid_mode;
	    var data = JSON.stringify(myJSON);
	    xh.open('PUT',"/ConfigSave?name=PID_tune",true); 
	    xh.setRequestHeader("Content-Type", "application/json");
	    xh.send(data);
		console.log(data);	
	  }
	}
 
 function SendData(){
 var xh = new XMLHttpRequest();
  if(xh.readyState==0||xh.readyState==4){
	  xh.onreadystatechange=function(){
	  if(xh.readyState==4&&xh.status==200){  
		  console.log("saved ok");
	  }
	}
	var res = JSON.parse(document.getElementById("send_data").value );
    var data = JSON.stringify(res);
    xh.open('PUT',"/ConfigSave?name=PID_tune",true); 
    xh.setRequestHeader("Content-Type", "application/json");				
    xh.send(data);
	console.log(data);	
  }
}
 
 function init(){
	 PidStatusLoad();
	 setInterval('PidStatusLoad()', 5000);
 }