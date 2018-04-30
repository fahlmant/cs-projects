from google.appengine.api import users
from google.appengine.ext import ndb

import webapp2
import json


class Slip(ndb.Model):
    number = ndb.IntegerProperty(required=True)
    current_boat = ndb.StringProperty()
    arrival_date = ndb.StringProperty()
    slip_id = ndb.StringProperty()


class SlipHandler(webapp2.RequestHandler):

    def put(self,id):
        slip = ndb.Key(urlsafe=id).get()
        slip_data = json.loads(self.requset.body)
        if 'number' in slip_data:
	    slip.number = slip_data['number']
	slip.put()
	slip_dict = slip.to_dict()
	self.response.write(json.dumps(slip_dict))

    def get(self, id=None):
        #If and ID is provided
	if id:
	    # Get the key
	    slip = ndb.Key(urlsafe=id).get()
            # If the slip exists
            if slip:
                # Return all the info about the slip
                slip_dict = slip.to_dict()
                slip_dict['self'] = '/slip/' + slip.key.urlsafe()
                slip_dict['slip_id'] = slip.key.urlsafe()
                self.response.write(json.dumps(slip_dict))
            # Error if a bad/old ID was given
            else:
                self.response.status = 405
                self.response.write(
                    "405 Error: Bad slip id. Does the slip exist?")
        # Show all slips if no ID is provided
        else:
            # Get all the slips in the db
            slips = Slip.query().fetch()
            slip_dict = {'Slips': []}
            # Write info about each slip into an array to send as resonse
            for slip in slips:
                slip_data = slip.to_dict()
                slip_data['self'] = '/slips/' + slip.key.urlsafe()
                slip_data['slip_id'] = slip.key.urlsafe()
                slip_dict['Slips'].append(slip_data)
            self.response.write(json.dumps(slip_dict))

    def post(self):
        # Get all the data from the request
        slip_data = json.loads(self.request.body)

        if Slip.query(Slip.number == slip_data['number']).get():
            self.response.status = 403
            self.response.write("403 Error: Slip with number exists")
            return

        # Create a new slip with the corresponding data
        slip = Slip(number=slip_data['number'],
                    current_boat='',
                    arrival_date='')
        # Create the boat in the db
        slip.put()
        # For printing a response, create a boat_dict
        slip_dict = slip.to_dict()
        # Set self and ID for the response
        slip_dict['self'] = '/slips/' + slip.key.urlsafe()
        slip_dict['slip_id'] = slip.key.urlsafe()
        self.response.write(json.dumps(slip_dict))
		
    def delete(self, id=None):
        # If an ID is provided
        if id:
            slip = ndb.Key(urlsafe=id).get()
            # If the ID is a valid slip, delete it from the db
            if slip:
            	slip_dict = slip.to_dict()
            	if(slip_dict['current_boat'] != ''):
            		boat_id = slip_dict['current_boat']
            		boat = ndb.Key(urlsafe=boat_id).get()
            		boat.at_sea = True
            		boat.put()
                slip.key.delete()
                self.response.write('Slip ' + str(id) + ' deleted')
        # Error if no ID is provided
        else:
            self.response.status = 403
            self.response.write(
                '403 Error: Please provide slip ID for deletion')


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

    def put(self,id):
        boat = ndb.Key(urlsafe=id).get()
	boat_data = json.loads(self.requset.body)
	if 'name' in boat_data:
	    boat.name = boat_data['name']
	if 'length' in boat_data:
	    boat.length = boat_data['length']
	if 'boay_type' in boat_data:
	    boat.boat_type = boat_data['boat_type']
	boat.put()
	boat_dict = boat.to_dict()
	self.response.write(json.dumps(boat_dict))

    # Get info about a boat or all boats
    def get(self, id=None):
        #If and ID is provided
        if id:
            # Get the key
            boat = ndb.Key(urlsafe=id).get()
            # If the boat exists
            if boat:
                # Return all the info about the boat
                boat_dict = boat.to_dict()
                boat_dict['self'] = '/boats/' + boat.key.urlsafe()
                boat_dict['boat_id'] = boat.key.urlsafe()
                self.response.write(json.dumps(boat_dict))
            # Error if a bad/old ID was given
            else:
                self.response.status = 405
                self.response.write(
                    "405 Error: Bad boat id. Does the boat exist?")
        # Show all boats if no ID is provided
        else:
            # Get all the boats in the db
            boats = Boat.query().fetch()
            boat_dict = {'Boats': []}
            # Write info about each boat into an array to send as resonse
            for boat in boats:
                boat_data = boat.to_dict()
                boat_data['self'] = '/boats/' + boat.key.urlsafe()
                boat_data['boat_id'] = boat.key.urlsafe()
                boat_dict['Boats'].append(boat_data)
            self.response.write(json.dumps(boat_dict))

    # Create a boat
    def post(self):
        # Get all the data from the request
        boat_data = json.loads(self.request.body)

        if Boat.query(Boat.name == boat_data['name']).get():
            self.response.status = 403
            self.response.write("403 Error: Boat with name exists")
            self.error = True
            return

        # Create a new boat with the corresponding data
        boat = Boat(name=boat_data['name'],
                    boat_type=boat_data['boat_type'],
                    length=boat_data['length'],
                    at_sea=True)
        # Create the boat in the db
        boat.put()
        # For printing a response, create a boat_dict
        boat_dict = boat.to_dict()
        # Set self and ID for the response
        boat_dict['self'] = '/boats/' + boat.key.urlsafe()
        boat_dict['boat_id'] = boat.key.urlsafe()
        self.response.write(json.dumps(boat_dict))
		
    # Delete a boat
    def delete(self, id=None):
        # If an ID is provided
        if id:
            boat = ndb.Key(urlsafe=id).get()
            boat_data = boat.to_dict()
            # If the ID is a valid boat, delete it from the db
            if boat:
            	if Slip.query(Slip.current_boat == id):
            		slip = Slip
            		slip.current_boat = ""
            		slip.arrival_date = ""
            		slip.put()
                boat.key.delete()
                self.response.write('Boat ' + str(id) + ' deleted')
            # Return an error if the ID doesn't exist
            else:
                self.response.status = 405
                self.response.write(
                    '405 Error: Bad boat ID. Does the boat exist?')
        # Error if no ID is provided
        else:
            self.response.status = 403
            self.response.write(
                '403 Error: Please provide boat ID for deletion')


class DockingHandler(webapp2.RequestHandler):

    # Use put to be able to have more than one 'argument'
    def put(self, id):
        body = json.loads(self.request.body)
        boat_id = body['boat_id']

        try:
            arrival_date = body['arrival_date']
        except:
            self.response.status = 403
            self.response.write('403 Error: Please provide arrival date')
            return
        if arrival_date == '':
            self.response.status = 403
            self.response.write('403 Error: Please provide arrival date')
            return
        try:
            boat = ndb.Key(urlsafe=boat_id).get()
        except:
            self.response.status = 403
            self.response.write('403 Error: Please provide valid boat ID')
            return
        try:
            slip = ndb.Key(urlsafe=id).get()
        except:
            self.response.status = 403
            self.response.write('403 Error: Please provide valid slip ID')
            return

        if slip.current_boat != '':
            self.response.status = 403
            self.response.write('403 Error: Slip is occupied')
        else:
            slip.arrival_date = body['arrival_date']
            slip.current_boat = boat_id
            boat.at_sea = False
            boat.put()
            slip.put()
            slip_dict = slip.to_dict()
            slip_dict['self'] = '/slip/' + slip.key.urlsafe()
            slip_dict['slip_id'] = slip.key.urlsafe()
            self.response.write('Put boat in slip')

    def delete(self, id):
        slip = ndb.Key(urlsafe=id).get()
        if slip:
        	slip_dict = slip.to_dict()
        	boat_id = slip_dict['current_boat']
        	boat = ndb.Key(urlsafe=boat_id).get()
        	slip.arrival_date =''
        	slip.current_boat =''
        	boat.at_sea = True
        	boat.put()
        	slip.put()
        else:
        	self.response.status = 403
        	self.response.write('403 Error: Please provide valid slip ID')	

class BoatInSlipHandler(webapp2.RequestHandler):

    def get(self, id):
        slip = ndb.Key(urlsafe=id).get()
        slip_dict = slip.to_dict()
        boat_id = slip_dict['current_boat']
        boat = ndb.Key(urlsafe=boat_id).get()
        # If the boat exists
        if boat:
            # Return all the info about the boat
            boat_dict = boat.to_dict()
            boat_dict['self'] = '/boats/' + boat.key.urlsafe()
            boat_dict['boat_id'] = boat.key.urlsafe()
            self.response.write(json.dumps(boat_dict))
        # Error if a bad/old ID was given
        else:
            self.response.status = 405
            self.response.write("405 Error: No boat in slip")

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/boats', BoatHandler),
    ('/boats/(.*)', BoatHandler),
    ('/slips', SlipHandler),
    ('/slips/(.*)/dock', DockingHandler),
    ('/slips/(.*)/boat', BoatInSlipHandler),
    ('/slips/(.*)', SlipHandler)
], debug=True)
