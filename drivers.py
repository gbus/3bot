from servo import Servo
from servo_config import channel_config

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
	__braketime		= 0.2	# secs between brakestep changes

	def stepfw( self ):
		pass

	def stepback( self ):
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
		fw = False
		if (lneutral > lposition):	# only checking left wheel
			fw = True

		while ( lneutral != lposition and rneutral != rposition ):
			pass
			

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
