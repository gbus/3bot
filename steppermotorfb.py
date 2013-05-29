#!/usr/bin/env python

from steppermotor import Motor

class MotorRef(Motor):
	def __init__(self, IOpins, direction, max_steps):
		self._refpin	= IOpins.pop()	# IOpins[4] is the reference pin
		self._pins	= IOpins
		self._refstatus	= 0
		self._direction	= direction	# 0 = cw; 1 = acw
		self._step	= -1		# -1 = NA; 0 = reference
		self._maxsteps	= max_steps
		Motor(self, pins)

	def _check_refstatus():
	"""Returns 0/1 according to reference GPIO value"""
		pass

	def reset_reference():
	"""Turn the motor until the reference is reached"""
		pass


