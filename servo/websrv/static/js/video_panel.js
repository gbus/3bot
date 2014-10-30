//
// Interface
//

$(document).ready(function () {
    $('#mjpeg_dest').imgAreaSelect({
        handles: true,
        onSelectEnd: set_roi
    });
});

$(document).ready(function(){
	$("#regionselAlert").bind('closed.bs.alert', reset_roi );
}); 


viewerAlert = function() {}
viewerAlert.warning = function(alertType, alertContent) {
	$('#viewerNotifications').html('<div id=regionselAlert class=alert alert-' + alertType + '> ' + alertContent + ' </div>')
}

function set_preset(value) {

  document.getElementById("video_width").value = value.substr(0, 4);
  document.getElementById("video_height").value = value.substr(5, 4);
  document.getElementById("video_fps").value = value.substr(10, 2);
  document.getElementById("MP4Box_fps").value = value.substr(13, 2);
  document.getElementById("image_width").value = value.substr(16, 4);
  document.getElementById("image_height").value = value.substr(21, 4);
  send_cmd("px", value);

}

function set_res() {
  
  while(document.getElementById("video_width").value.length < 4) document.getElementById("video_width").value = "0" + document.getElementById("video_width").value;
  while(document.getElementById("video_height").value.length < 4) document.getElementById("video_height").value = "0" + document.getElementById("video_height").value;
  while(document.getElementById("video_fps").value.length < 2) document.getElementById("video_fps").value = "0" + document.getElementById("video_fps").value;
  while(document.getElementById("MP4Box_fps").value.length < 2) document.getElementById("MP4Box_fps").value = "0" + document.getElementById("MP4Box_fps").value;
  while(document.getElementById("image_width").value.length < 4) document.getElementById("image_width").value = "0" + document.getElementById("image_width").value;
  while(document.getElementById("image_height").value.length < 4) document.getElementById("image_height").value = "0" + document.getElementById("image_height").value;
  
  send_cmd("px", document.getElementById("video_width").value + " " + document.getElementById("video_height").value + " " + document.getElementById("video_fps").value + " " + document.getElementById("MP4Box_fps").value + " " + document.getElementById("image_width").value + " " + document.getElementById("image_height").value);

}

function set_ce() {
  
  while(document.getElementById("ce_u").value.length < 3) document.getElementById("ce_u").value = "0" + document.getElementById("ce_u").value;
  while(document.getElementById("ce_v").value.length < 3) document.getElementById("ce_v").value = "0" + document.getElementById("ce_v").value;
  
  send_cmd("ce", document.getElementById("ce_en").value + " " + document.getElementById("ce_u").value + " " + document.getElementById("ce_v").value);

}

function set_roi(img,selection) {
  if (!selection.width || !selection.height)
        return;
  // x,y,w,h rescaled on a 0-65535 range
  var xr = Math.round(selection.x1/img.clientWidth*65535);
  var yr = Math.round(selection.y1/img.clientHeight*65535);
  var wr = Math.round(selection.width/img.clientWidth*65535);
  var hr = Math.round(selection.height/img.clientHeight*65535);
  
  // 0 padded to 5 chars
  var xrstr = xr.toString();
  var yrstr = yr.toString();
  var wrstr = wr.toString();
  var hrstr = hr.toString();
  while(xrstr.length < 5) xrstr = "0" + xrstr;
  while(yrstr.length < 5) yrstr = "0" + yrstr;
  while(wrstr.length < 5) wrstr = "0" + wrstr;
  while(hrstr.length < 5) hrstr = "0" + hrstr;

  // Trigger an info alert that shows the selected range in pixels
  viewerAlert.warning('info', '<button type=button class=close data-dismiss=alert><span class=glyphicon glyphicon-retweet> Reset</button> Region selected from ('+selection.x1+','+selection.y1+') to ('+selection.x2+','+selection.y2+').');

  send_cmd("ri", xrstr + " " + yrstr + " " + wrstr + " " + hrstr );
}

function reset_roi(){
	send_cmd("ri", "0 0 65535 65535" );
    }



//
// Shutdown
//
function sys_shutdown() {
  ajax_status.open("GET", "cmd_func.php?cmd=shutdown", true);
  ajax_status.send();
}

function sys_reboot() {
  ajax_status.open("GET", "cmd_func.php?cmd=reboot", true);
  ajax_status.send();
}

//
// MJPEG
//
var mjpeg_img;
var halted = 0;

function reload_img () {
  if(!halted) mjpeg_img.src = "/camera/image?time=" + new Date().getTime();
  else setTimeout("reload_img()", 500);
}

function error_img () {
  setTimeout("mjpeg_img.src = '/camera/image?time=' + new Date().getTime();", 100);
}

//
// Ajax Status
//
var ajax_status;

if(window.XMLHttpRequest) {
  ajax_status = new XMLHttpRequest();
}
else {
  ajax_status = new ActiveXObject("Microsoft.XMLHTTP");
}


ajax_status.onreadystatechange = function() {
  if(ajax_status.readyState == 4 && ajax_status.status == 200) {

    if(ajax_status.responseText == "ready") {
      document.getElementById("video_button").disabled = false;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {send_cmd("ca", "1");};
      document.getElementById("image_button").disabled = false;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {send_cmd("im", "");};
      document.getElementById("timelapse_button").disabled = false;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {send_cmd("tl", (document.getElementById("tl_interval").value*10));};
      document.getElementById("md_button").disabled = false;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {send_cmd("md", "1");};
      document.getElementById("halt_button").disabled = false;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {send_cmd("ru", "0");};
      halted = 0;
    }
    else if(ajax_status.responseText == "md_ready") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = false;
      document.getElementById("md_button").value = "motion detection stop";
      document.getElementById("md_button").onclick = function() {send_cmd("md", "0");};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
      halted = 0;
    }
    else if(ajax_status.responseText == "video") {
      document.getElementById("video_button").disabled = false;
      document.getElementById("video_button").value = "record video stop";
      document.getElementById("video_button").onclick = function() {send_cmd("ca", "0");};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "timelapse") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = false;
      document.getElementById("timelapse_button").value = "timelapse stop";
      document.getElementById("timelapse_button").onclick = function() {send_cmd("tl", "0");};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "md_video") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "recording video...";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "image") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "recording image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "boxing") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "video processing...";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "md_boxing") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "video processing...";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = true;
      document.getElementById("halt_button").value = "stop camera";
      document.getElementById("halt_button").onclick = function() {};
    }
    else if(ajax_status.responseText == "halted") {
      document.getElementById("video_button").disabled = true;
      document.getElementById("video_button").value = "record video start";
      document.getElementById("video_button").onclick = function() {};
      document.getElementById("image_button").disabled = true;
      document.getElementById("image_button").value = "record image";
      document.getElementById("image_button").onclick = function() {};
      document.getElementById("timelapse_button").disabled = true;
      document.getElementById("timelapse_button").value = "timelapse start";
      document.getElementById("timelapse_button").onclick = function() {};
      document.getElementById("md_button").disabled = true;
      document.getElementById("md_button").value = "motion detection start";
      document.getElementById("md_button").onclick = function() {};
      document.getElementById("halt_button").disabled = false;
      document.getElementById("halt_button").value = "start camera";
      document.getElementById("halt_button").onclick = function() {send_cmd("ru", "1");};
      halted = 1;
    }
    else if(ajax_status.responseText.substr(0,5) == "Error") alert("Error in RaspiMJPEG: " + ajax_status.responseText.substr(7) + "\nRestart RaspiMJPEG (./RPi_Cam_Web_Interface_Installer.sh start) or the whole RPi.");
    
    reload_ajax(ajax_status.responseText);

  }
}

function reload_ajax (last) {
  ajax_status.open("GET","/raspimjpeg/status/" + last,true);
  ajax_status.send();
}


//
// Ajax Commands
//
var ajax_cmd;

if(window.XMLHttpRequest) {
  ajax_cmd = new XMLHttpRequest();
}
else {
  ajax_cmd = new ActiveXObject("Microsoft.XMLHTTP");
}

function send_cmd (cmd, value) {
  ajax_cmd.open("GET","raspimjpeg/" + cmd + "/" + value,true);
  ajax_cmd.send();
}

//
// Init
//
function init() {

  // mjpeg
  mjpeg_img = document.getElementById("mjpeg_dest");
  mjpeg_img.onload = reload_img;
  mjpeg_img.onerror = error_img;
  reload_img();
  // status
  reload_ajax("");

}
