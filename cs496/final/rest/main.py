from google.appengine.api import users
from google.appengine.ext import ndb

import webapp2
import json


class Book(ndb.Model):

    title = ndb.StringProperty(required=True)
    author = ndb.StringProperty(required=True)
    language = ndb.StringProperty(required=True)
    isbn = ndb.StringProperty(required=True)
    shelf = ndb.StringProperty()

class Shelf(ndb.Model):

    room = ndb.StringProperty(required=True)
    size = ndb.IntegerProperty(required=True)
    number = ndb.IntegerProperty(required=True)
    genre = ndb.StringProperty()
    book = ndb.StringProperty(repeated=True)

class BookHandler(webapp2.RequestHandler):

    def get(self, id=None):
        if id:
            book = ndb.Key(urlsafe=id).get()
            if book:
                book_dict = book.to_dict()
                book_dict['self'] = '/books/' + book.key.urlsafe()
                book_dict['book_id'] = book.key.urlsafe()
                self.response.write(json.dumps(book_dict))
            else:
                self.response.status = 405
                self.response.write("405 Error: ")
        else:
            books = Book.query().fetch()
            book_dict = {'Books': []}
            for book in books:
                book_data = book.to_dict()
                book_data['self'] = '/books/' + book.key.urlsafe()
                book_data['book_id'] = book.key.urlsafe()
                book_dict['Books'].append(book_data)
            self.response.write(json.dumps(book_dict))

    def post(self):
        book_data = json.loads(self.request.body)

        book = Book(title=book_data['title'],
                    author='foo',
                    language='bar',
                    isbn='baz')
        book.put()
        book_dict = book.to_dict()
        book_dict['self'] = '/books/' + book.key.urlsafe()
        book_dict['book_id'] = book.key.urlsafe()
        self.response.write(json.dumps(book_dict))


class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write("Hello, final project")

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/books', BookHandler),
    ('/books/(.*)', BookHandler)
], debug=True)
