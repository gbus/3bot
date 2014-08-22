import logging
import time
import sys

from daemon import runner
#import RPi.GPIO as GPIO


class App():
	def __init__(self):
		self.stdin_path = '/dev/null'
		self.stdout_path = '/dev/tty'
		self.stderr_path = '/dev/tty'
		self.pidfile_path =  '/var/run/testdaemon/testdaemon.pid'
		self.pidfile_timeout = 5
		self.rec_button = 17
		self.recording = False
		#GPIO.setmode(GPIO.BCM)
		#GPIO.setup(self.rec_button, GPIO.IN, pull_up_down=GPIO.PUD_UP)
		#GPIO.add_event_detect(self.rec_button, GPIO.RISING)

	def run(self):
		while True:
			# Check button pushed
                        #if GPIO.event_detected(rec_button):
			if self.recording==True:
				self.recording=False
				logger.info("Stop recording")
				# Stop capturing
			else:
				self.recording=True
				logger.info("Start recording")
				# Start capturing 

			# If recording read metrics from 9 axis sensor and get frame id
			# append all to logging file
			if recording:
				# Get gyro metrics

			time.sleep(1)

app = App()
logger = logging.getLogger("DaemonLog")
logger.setLevel(logging.INFO)
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
handler = logging.FileHandler("/var/log/testdaemon/testdaemon.log")
handler.setFormatter(formatter)
logger.addHandler(handler)

daemon_runner = runner.DaemonRunner(app)
daemon_runner.daemon_context.files_preserve=[handler.stream]
daemon_runner.do_action()

#GPIO.cleanup(rec_button)

