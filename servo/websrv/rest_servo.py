import os
import inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
os.sys.path.insert(0,parentdir) 


import web
import json
from servo import Servo



render = web.template.render('templates/')

urls = (
  '/', 'index',
  '/interface2', 'interface2',
  '/servo/neutral/(.*)', 'Reset',
  '/servo/position/(.*)/(.*)', 'Position',
  '/servo/step/(.*)/(.*)', 'Step',
  '/servo/minposition/(.*)', 'SetMin',
  '/servo/maxposition/(.*)', 'SetMax',
  '/servo/config/(.*)', 'GetConf',
)


s = Servo()

class Reset:
	def GET(self, channel):
		s.set_channel( int(channel) )
		ret = s.reset_position()
		web.header('Content-Type', 'application/json')
		return json.dumps( {'pos': ret, 'channel': channel} ) 
    	
class Position:
	def GET(self, channel, pos):
		s.set_channel( int(channel) )
		ret = s.set_position( int(pos) )
		web.header('Content-Type', 'application/json')
		return json.dumps( {'pos': ret, 'channel': channel} )

class Step:
	def GET(self, channel, step):
		s.set_channel( int(channel) )
		ret = s.step_position( int(step) )
		web.header('Content-Type', 'application/json')
		return json.dumps( {'pos': ret, 'channel': channel} )
    
class SetMin:
	def GET(self, channel):
		s.set_channel( int(channel) )
		ret = s.set_position( s.min_pos )
		web.header('Content-Type', 'application/json')
		return json.dumps( {'pos': ret, 'channel': channel} )
    
    
class SetMax:
	def GET(self, channel):
		s.set_channel( int(channel) )
		ret = s.set_position( s.max_pos )
		web.header('Content-Type', 'application/json')
		return json.dumps( {'pos': ret, 'channel': channel} )

class GetConf:
	def GET(self, channel):
		s.set_channel( int(channel) )
		ret = s.get_servo_conf()
		web.header('Content-Type', 'application/json')
		return json.dumps( ret )

class index:
    def GET(self):
		return render.index()

class interface2:
    def GET(self):
		return render.interface2()
        
if __name__ == "__main__": 
    app = web.application(urls, globals())
    app.run()   