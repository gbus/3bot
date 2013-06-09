#!/usr/local/bin/python

import curses
#from espeak import espeak
from drivers import Drive2
from servo import Servo
from servo_config import channel_config
import RPi.GPIO as GPIO
from steppermotor import Motor


# SERVO CONFIG
lw_channel	= 0
rw_channel	= 1
x_channel	= 4
y_channel	= 5
le_gpio		= 28
li_gpio		= 29

# INIT VALUES
#lw	= Servo(lw_channel)	# Left wheel servo
#rw	= Servo(rw_channel)	# Right wheel servo
wheels	= Drive2(lw_channel, rw_channel)
x	= Servo(x_channel)	# Head Tilt
y	= Servo(y_channel)	# Head Pan
leds	= False			# LEDs
light	= False			# Light


xret = x.reset_position()
yret = y.reset_position()
#lret = lw.reset_position()
#rret = rw.reset_position()

# CURSES INIT
screen = curses.initscr()
curses.noecho() 
curses.curs_set(0) 
screen.keypad(1)

# Init GPIO values
GPIO.setmode(GPIO.BCM)
GPIO.setup(le_gpio, GPIO.OUT)
GPIO.output(le_gpio, GPIO.LOW)
GPIO.setup(li_gpio, GPIO.OUT)
GPIO.output(li_gpio, GPIO.LOW)

# INIT STEPPER MOTORS
nsteps = 50
jointA = Motor([4,17,27,22])
jointA.rpm = 2
jointB = Motor([18,23,24,25])
jointB.rpm = 10


initmsg = "3Bot ready to go!"
spinningmsg = "YUUUUU, I'm spinning fast!"
screen.addstr(initmsg)
#espeak.synth(initmsg)

stepvalue = 10


talk = True

while True: 
   event = screen.getch() 
   if event == ord("q"): break 
   elif event == ord("w"):
      xret = x.step_position(-stepvalue)
   elif event == ord("s"):
      xret = x.step_position(stepvalue)
   elif event == ord("a"):
      yret = y.step_position(stepvalue)
   elif event == ord("d"):
      yret = y.step_position(-stepvalue)
   elif event == ord("e"):
      jointA._move_cw(nsteps)     # extend
   elif event == ord("r"):
      jointA._move_acw(nsteps)     # retract
   elif event == ord("t"):
      jointB._move_cw(nsteps)
   elif event == ord("y"):
      jointB._move_acw(nsteps)
   elif event == ord("l"):
      if leds:
          GPIO.output(le_gpio, GPIO.LOW)
          leds = False
      else:
          GPIO.output(le_gpio, GPIO.HIGH)
          leds = True
   elif event == ord("L"):
      if light:
          GPIO.output(li_gpio, GPIO.LOW)
          light = False
      else:
          GPIO.output(li_gpio, GPIO.HIGH)
          light = True
   elif event == curses.KEY_UP: 
      #lret = lw.step_position(-stepvalue)
      #rret = rw.step_position(stepvalue)
      wheels.onemovefw(20,1)
   elif event == curses.KEY_DOWN:
      #lret = lw.step_position(stepvalue)
      #rret = rw.step_position(-stepvalue)
      wheels.onemoveback(20,1)
   elif event == curses.KEY_LEFT:
      #lret = lw.step_position(stepvalue)
      #rret = rw.step_position(stepvalue)
      wheels.turnleft(20,1)
   elif event == curses.KEY_RIGHT:
      #lret = lw.step_position(-stepvalue)
      #rret = rw.step_position(-stepvalue)
      wheels.turnright(20,1)
   elif event == ord(' '):   
      #lret = lw.reset_position()
      #rret = rw.reset_position() 
      #xret = x.reset_position()
      #yret = y.reset_position()
      wheels.brake(20,1)

   screen.clear()      
#   screen.addstr("Wheel: l: %d; r: %d\n" % (lret, rret) )
#   screen.addstr("Head : x: %d; y: %d\n" % (xret, yret) )
   





GPIO.cleanup()
curses.endwin()
