from google.appengine.api import urlfetch
from google.appengine.ext.webapp import template

import webapp2
import json
import random
import string
import urllib
import threading

from webapp2_extras import sessions

CLIENT_ID = ""
CLIENT_SECRET = ""
ENDPOINT_URL_BASE = "https://accounts.google.com/o/oauth2/v2/auth?"


class OAuthHandler(webapp2.RequestHandler):
    def get(self):
        header = {'Content-Type':'application/x-www-form-urlencoded'}
        code = self.request.GET['code']
        returned_state = self.request.GET['state']

        verified = 'False'

        if(returned_state == app.registry.get('state')):
            verified = 'True'
        else:
            self.response.status = 403
            self.response.write('403: Error, State did not match')
            return

        payload_data = {
                'code':code,
                'client_id':CLIENT_ID,
                'client_secret':CLIENT_SECRET,
                'redirect_uri':'https://cs496-oauth-fahlmant.appspot.com/oauth',
                'grant_type':'authorization_code'
                }
        payload_encoded_data = urllib.urlencode(payload_data)

        response = urlfetch.fetch(
                "https://www.googleapis.com/oauth2/v4/token/",
                headers=header,
                payload=payload_encoded_data,
                method=urlfetch.POST)

        json_response = json.loads(response.content)

        token = json_response['access_token']
        header = {'Authorization': 'Bearer ' + token}
        response = urlfetch.fetch(
                "https://www.googleapis.com/plus/v1/people/me",
                headers=header
                )

        user_data = json.loads(response.content)
        fname = user_data['name']['givenName']
        lname = user_data['name']['familyName']
        email = user_data['emails'][0]['value']

        template_data = {
                'fname': fname,
                'lname': lname,
                'email': email,
                'verified_state': returned_state,
                'verified':verified
                }

        self.response.write(template.render('templates/oauth.html', template_data))



class MainPage(webapp2.RequestHandler):
    def get(self):

		#Get the app itself for access to registry
        app = webapp2.get_app()

        #Generate the state variable
        random_state = ''
        for i in range(0,32):
            #https://stackoverflow.com/questions/2823316/generate-a-random-letter-in-python
            x = random.choice(string.ascii_letters + string.digits)
            random_state += x
		#Set the registry key to the random string
        app.registry['state'] = random_state

		#Build the URL using the client ID, random state, email scope and redirect url to the local oauth endpoint
        endpoint_built_url = ENDPOINT_URL_BASE +\
                'response_type=code' +\
                '&client_id=' + CLIENT_ID +\
                '&scope=email' +\
                '&state=' + random_state +\
                '&redirect_uri=https://cs496-oauth-fahlmant.appspot.com/oauth'

		#Load the url and state into a value to be rendered in the template
        template_value = {'google_auth_url':endpoint_built_url,
                          'state':random_state}

		#Render index.html with url as the href of the button, show the state for testing
        self.response.write(template.render('templates/index.html', template_value))

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/oauth', OAuthHandler)
], debug=True)