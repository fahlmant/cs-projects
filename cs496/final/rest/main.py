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
    books = ndb.StringProperty(repeated=True)

class BookHandler(webapp2.RequestHandler):

    #List one or all books
    def get(self, id=None):
        #If a book ID is specified
        if id:
            book = ndb.Key(urlsafe=id).get()
            #If the book exists return its info
            if book:
                book_dict = book.to_dict()
                book_dict['self'] = '/books/' + book.key.urlsafe()
                book_dict['book_id'] = book.key.urlsafe()
                self.response.write(json.dumps(book_dict))
            #If the book doesn't exist return an error
            else:
                response = {"Result":404, "Message":"Book does not exist"}
                self.response.status = 404
                self.response.write(json.dumps(response))
        #If no book ID is specified, return all books
        else:
            books = Book.query().fetch()
            book_dict = {'Books': []}
            for book in books:
                book_data = book.to_dict()
                book_data['self'] = '/books/' + book.key.urlsafe()
                book_data['book_id'] = book.key.urlsafe()
                book_dict['Books'].append(book_data)
            self.response.write(json.dumps(book_dict))

    #Create a book
    def post(self):
        book_data = json.loads(self.request.body)

        book = Book(title=book_data['title'],
                    author=book_data['author'],
                    language=book_data['language'],
                    isbn=book_data['isbn'],
                    shelf='')
        book.put()
        book_dict = book.to_dict()
        book_dict['self'] = '/books/' + book.key.urlsafe()
        book_dict['book_id'] = book.key.urlsafe()
        self.response.write(json.dumps(book_dict))

    def delete(self, id):
        if id:
            book = ndb.Key(urlsafe=id).get()
            if book:
                book_dict = book.to_dict()
                #handle book in shelf here
                book.key.delete()
                response = {"Result":204, "Message":"Book deleted"}
                self.response.write(json.dumps(response))
            else:
                response = {"Result":403, "Message":"Error: Book not found"}
                self.response.status = 403
                self.response.write(json.dumps(response))

        else:
            response ={"Result":403, "Message":"Error: Book not found"}
            self.response.status = 403
            self.response.write(json.dumps(response))

    def put(self):
        pass


class ShelfHandler(webapp2.RequestHandler):
 
    def get(self, id=None):
        if id:
            shelf = ndb.Key(urlsafe=id).get()
            if shelf:
                shelf_dict = shelf.to_dict()
                shelf_dict['self'] = '/shelves/' + shelf.key.urlsafe()
                shelf_dict['shelf_id'] = shelf.key.urlsafe()
                self.response.write(json.dumps(shelf_dict))
            else:
                self.response.status = 405
                self.response.write("405 Error: ")
        else:
            shelves = Shelf.query().fetch()
            shelf_dict = {'Shelves': []}
            for shelf in shelves:
                shelf_data = shelf.to_dict()
                shelf_data['self'] = '/shelves/' + shelf.key.urlsafe()
                shelf_data['shelf_id'] = shelf.key.urlsafe()
                shelf_dict['Shelves'].append(shelf_data)
            self.response.write(json.dumps(shelf_dict))

    def post(self):
        shelf_data = json.loads(self.request.body)

        shelf = Shelf(room=shelf_data['room'],
                    size=shelf_data['size'],
                    number=shelf_data['number'],
                    genre=shelf_data['genre'],
                    books=shelf_data['books'])
        shelf.put()
        shelf_dict = shelf.to_dict()
        shelf_dict['self'] = '/shelves/' + shelf.key.urlsafe()
        shelf_dict['shelf_id'] = shelf.key.urlsafe()
        self.response.write(json.dumps(shelf_dict))

    def delete(self, id):
        pass

    def put(self):
        pass
   
class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write("Hello, final project")

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/books', BookHandler),
    ('/books/(.*)', BookHandler),
    ('/shelves', ShelfHandler),
    ('/shelves/(.*)', ShelfHandler)

], debug=True)
