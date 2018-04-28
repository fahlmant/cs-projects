from google.appengine.api import users
from google.appengine.ext import ndb

import webapp2
import json

class Boat(ndb.Model):
    name = ndb.StringProperty(required=True)
    boat_type = ndb.StringProperty(required=True)
    length = ndb.IntegerProperty(required=True)
    at_sea = ndb.BooleanProperty()
    boat_id = ndb.StringProperty()
	
class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write("Hello")

class BoatHandler(webapp2.RequestHandler):
    def get(self, id=None):
        if id:
            boat = ndb.Key(urlsafe=id).get()
            if boat:
                boat_dict = boat.to_dict()
                boat_dict['self'] = '/boats/' + boat.key.urlsafe()
                boat_dict['boat_id'] = boat.key.urlsafe()
                self.response.write(json.dumps(boat_dict))
            else:
                self.response.status = 405
                self.response.write("Bad id")
        else:
            boats = Boat.query().fetch()
            boat_dict = {'Boats':[]}
            for boat in boats:
                boat_data = boat.to_dict()
                boat_data['self'] = '/boats/' + boat.key.urlsafe()
                boat_data['boat_id'] = boat.key.urlsafe()
                boat_dict['Boats'].append(boat_data)
            self.response.write(json.dumps(boat_dict))

    def post(self):
        boat_data = json.loads(self.request.body)
        boat = Boat(name=boat_data['name'],
                    boat_type=boat_data['boat_type'],
                    length=boat_data['length'],
                    at_sea=True)
        boat.put()
        boat_dict = boat.to_dict()
        boat_dict['self'] = '/boats/' + boat.key.urlsafe()
        boat_dict['boat_id'] = boat.key.urlsafe()
        self.response.write(json.dumps(boat_dict))

    def delete(self,id=None):
        if id:
            boat = ndb.Key(urlsafe=id).get()
            if boat:
                boat.key.delete()
                self.response.write('Boat ' + str(id) + ' deleted')
            else:
                self.response.status = '405'
                self.response.write('Bad boat ID')
        else:
            self.response.status = '403'
            self.response.write('ERROR: Please provide ID for deletion')


app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/boats', BoatHandler),
    ('/boats/(.*)', BoatHandler)
], debug=True)
