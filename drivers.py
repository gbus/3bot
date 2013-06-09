from servo import Servo
from time import sleep

# SERVO CONFIG
lw_channel		= 0
rw_channel		= 1
head_tilt_channel	= 4
head_pan_channel	= 5



class Drive2:
	"""controls two servos driving a three wheels platform
	:param lw_channel: PWM channel for left wheel
	:param rw_channel: PWM channel for right wheel
	"""

	__brakestep		= 20	# how much reduce the speed at each cycle
	__brakedelay		= 0.2	# secs between brakestep changes

	def __init__(self, lw_channel, rw_channel):
		self.lw	= Servo(lw_channel)
		self.rw	= Servo(rw_channel)

	def onemovefw( self, speed_increment, duration ):
		ldir = -1; rdir = 1
		self.__onemove( speed_increment, duration, ldir, rdir )

	def onemoveback( self, speed_increment, duration ):
		ldir = 1; rdir = -1
		self.__onemove( speed_increment, duration, ldir, rdir )

	def turnleft( self, speed_increment, duration ):
		ldir = 1; rdir = 1
		self.__onemove( speed_increment, duration, ldir, rdir )

	def turnright( self, speed_increment, duration ):
		ldir = -1; rdir = -1
		self.__onemove( speed_increment, duration, ldir, rdir )

	def __onemove( self, speed_increment, duration, ldir, rdir ):
		"""smoothly increase and decrease the speed for left and right servos 
		:param speed_increment: how much increase the speed
		:param duration: how long keep the requested speed
		:param ldir: left wheel direction (-1: fw, +1: back)
		:param rdir: right wheel direction (+1: fw, -1: back)
		"""
		num_steps	= 5	# progressively increase/decrease the speed
		step_size	= abs(speed_increment/num_steps)
		# speedup
		for s in range(step_size,speed_increment,step_size):
			self.lw.step_position(ldir*s)
			self.rw.step_position(rdir*s)
			sleep(0.5)
		# keep top speed for a given time
		self.lw.step_position(ldir*speed_increment)
		self.rw.step_position(rdir*speed_increment)
		sleep(duration)
		# slowdown
		for s in range(speed_increment,step_size,-step_size):
			self.lw.step_position(ldir*s)
			self.rw.step_position(rdir*s)
			sleep(0.5)
		# ensure servos are stopped
		self.lw.reset_position()
		self.rw.reset_position()

	def speedup( self, speed_increment ):
		lret = self.lw.step_position(-speed_increment)
		rret = self.rw.step_position(speed_increment)

	def slowdown( self, speed_increment ):
		lret = self.lw.step_position(speed_increment)
		rret = self.rw.step_position(-speed_increment)

	def brake( self ):
		lneutral	= self.lw.get_neutral_pos()
		lposition	= self.lw.get_current_pos()
		rneutral	= self.rw.get_neutral_pos()
		rposition	= self.rw.get_current_pos()
		
		# check direction
		ldir = -1; rdir = 1	# default to forward direction
		if (lneutral < lposition or rneutral > rposition):	# moving backward
			ldir = 1; rdir = -1

		while ( lneutral != lposition and rneutral != rposition ):

			# Slow down left
			if (lneutral != lposition):	# left is still moving
				lposition = lposition - ( ldir * __brakestep )
				if (abs(lposition-lneutral)<__brakestep):	# lposition too close to neutral
					lposition = lneutral
				self.lw.step_position(lposition)

			# Slow down right
			if (rneutral != rposition):	# right is still moving
				rposition = rposition - ( rdir * self.__brakestep )
				if (abs(rposition-rneutral)<self.__brakestep):	# rposition too close to neutral
					rposition = rneutral
				self.rw.step_position(rposition)

			sleep(self.__brakedelay)
			


class Backbone:
	"""controls stepper motors to extend/retract a two joints robot backbone

		           ^
		            \
		             \
		              \
		               \     <---------
		               ^              ^
	<----------           /               |
	     ----->          /                |
	   .---.          .---.             .---.
	   |   |          |   |             |   |
	   O  -'          O  -'             O  -'
		                               
	 .---------.    .-----------.    .-----------.
	 Retracted      Extended UP      Extended FW

	:param lowjoint_conf: list of 4 GPIO ports for the low stepper and 1 GPIO for the low switch sensor
	:param hijoint_conf: list of 4 GPIO ports for the high stepper and 1 GPIO for the high switch sensor
	"""


	def __init__(self, lowjoint_conf, hijoint_conf):
		self.lowsensor_port = lowjoint_conf.pop()
		self.hisensor_port = hijoint_conf.pop()
		# Create 2 stepper instances
		self.lowjoint	= Motor(lowjoint_conf)
		self.hijoint	= Motor(hijoint_conf)





class Switch:
	"""buttons to switch things on/off
	:param none: nodesc
	"""
	pass
