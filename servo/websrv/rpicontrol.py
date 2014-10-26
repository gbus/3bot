
status_file = "/home/pi/3bot/servo/websrv/static/raspicam/status_mjpeg'

def raspimjpeg_status(last):
	sf = open (status_file, 'r')
	current = sf.read()
	if (current != last):
		return current
	else return last 
