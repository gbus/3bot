from servo import Servo
from servo_config import channel_config
from time import sleep

# SERVO CONFIG
lw_channel		= 0
rw_channel		= 1
head_tilt_channel	= 4
head_pan_channel	= 5



class drive2:
	"""controls two servos driving a three wheels platform
	:param none: nodesc
	"""
	lw	= Servo(lw_channel)	# Left wheel servo
	rw	= Servo(rw_channel)	# Right wheel servo
	__speedinc		= 10
	__turnstep		= 10
	__brakestep		= 20	# how many steps reduce the speed at each cycle
	__brakedelay	= 0.2	# secs between brakestep changes
	__movespeed		= 20 
	__moveduration	= 2		# secs the servo keep spinning

	def onemovefw( self ):
		pass

	def onemoveback( self ):
		pass

	def turnleft( self ):
		pass

	def turnright( self ):
		pass

	def speedup( self ):
		lret = lw.step_position(-__speedinc)
		rret = rw.step_position(__speedinc)

	def slowdown( self ):
		lret = lw.step_position(__speedinc)
		rret = rw.step_position(-__speedinc)

	def brake( self ):
		lneutral	= lw.get_neutral_pos()
		lposition	= lw.get_current_pos()
		rneutral	= rw.get_neutral_pos()
		rposition	= rw.get_current_pos()
		
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
				lw.step_position(lposition)

			# Slow down right
			if (rneutral != rposition):	# right is still moving
				rposition = rposition - ( rdir * __brakestep )
				if (abs(rposition-rneutral)<__brakestep):	# rposition too close to neutral
					rposition = rneutral
				rw.step_position(rposition)

			sleep(__brakedelay)
			

class switch:
	"""buttons to switch things on/off
	:param none: nodesc
	"""
	pass

class backbone:
	"""controls steper motors to extend/retract robot backbone
	:param none: nodesc
	"""
	pass
