from google.appengine.api import users
from google.appengine.ext import ndb

import webapp2
import json

class Boat(ndb.Model):
	name = ndb.StringProperty(required=True)
	type = ndb.StringProperty(required=True)
	length = ndb.IntegerProperty(required=True)
	at_sea = ndb.BooleanProperty()
	id = ndb.StringProperty()
	
class MainPage(webapp2.RequestHandler):
	def get(self):
		self.response.write("Hello")

class BoatHandler(webapp2.RequestHandler):
#	def get(self):
#		self.response.write("Boats")
	def post(self):
		boat_data = json.loads(self.request.body)
		self.response.write(json.dumps(boat_data))


app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/boats', BoatHandler)
], debug=True)