/*!
 * slider to control xy servos
 * uses ajax to control restful interface to servos
 * Date: 2014-10-07
 */


var webserver_address = location.host;

var y_channel = 12
var x_channel = 11
var position_url  = 'http://' + webserver_address + '/servo/position'
var settings_url  = 'http://' + webserver_address + '/servo/config'


function loadSettings (url, ch, slider_name) {
    var PageUrl = url + '/' + ch;
    var data;

    //Load the data in using jQuerys ajax call
    $.ajax({
        url:PageUrl,
        dataType:'json',
        async: false,
        success:function (data) {
            $(slider_name).slider({
                min: data.minp,
                max: data.maxp,
	        value: data.minp + (data.maxp-data.minp)/2
            });
	}
    });
}



function loadRestfulData (url, ch, val) {
    var PageUrl = url + '/' + ch+'/' + val;
    //Set the content pane to a loading screen
    $('#content-pane').text('Changing status...');
    //Load the data in using jQuerys ajax call
    $.ajax({
        url:PageUrl,
        dataType:'json',
        success:function (data) {
            //Once we receive the data, set it to the content pane.
            $('#content-pane').text("Channel: "+data["channel"]+" Position: "+data["pos"]);
        }
    });
}


// Get min,max for slides with REST calls
loadSettings (settings_url, x_channel, '#xpos');
loadSettings (settings_url, y_channel, '#ypos')


$( "#xpos" ).slider({
    formatter: function(value) {
        return 'Current value: ' + value;
    }
});

$("#xpos").on("slide", function(slideEvt) {
	loadRestfulData(position_url, x_channel, slideEvt.value)
	$("#xposSliderVal").text(slideEvt.value);
});


$( "#ypos" ).slider({
    formatter: function(value) {
        return 'Current value: ' + value;
    }
});

$("#ypos").on("slide", function(slideEvt) {
	loadRestfulData(position_url, y_channel, slideEvt.value)
	$("#yposSliderVal").text(slideEvt.value);
});


