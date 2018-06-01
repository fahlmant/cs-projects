from google.appengine.api import users
from google.appengine.ext import ndb

import webapp2
import json


class EntityOne(ndb.Model):
    number = ndb.IntegerProperty(required=True)

class EntityTwo(ndb.Model):
    number = ndb.IntegerProperty(required=True)


class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write("Hello, final project")

app = webapp2.WSGIApplication([
    ('/', MainPage),
], debug=True)
