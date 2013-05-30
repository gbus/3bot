/*!
 * slider to control xy servos
 * uses ajax to control restful interface to servos
 * Date: 2013-2-19
 */


var webserver_address = location.host;

var y_channel = 5
var x_channel = 4
var position_url  = 'http://' + webserver_address + '/servo/position'
var settings_url  = 'http://' + webserver_address + '/servo/config'
var slide_step = 10

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



$( "#xpos" ).slider({
    step: slide_step,

    create: function(event, ui) {
        loadSettings (settings_url, x_channel, '#xpos')
    },

    slide: function( event, ui ) {
	loadRestfulData(position_url, x_channel, ui.value)
    	$( "#xcurrent" ).val( $( "#xpos" ).slider( "value" ) );
    }
});

$( "#ypos" ).slider({
    orientation: "vertical",
    step: slide_step,

    create: function(event, ui) {
        loadSettings (settings_url, y_channel, '#ypos')
    },

    slide: function( event, ui ) {
	loadRestfulData(position_url, y_channel, ui.value)
    	$( "#ycurrent" ).val( ui.value );
    }
});
