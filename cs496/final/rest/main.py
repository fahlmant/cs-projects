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
    genre = ndb.StringProperty()
    number = ndb.StringProperty(required=True)
    wood  = ndb.StringProperty(required=True)
    book = ndb.StringProperty()

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
            #Get book by ID
            book = ndb.Key(urlsafe=id).get()
            #Get all info about book
            book_dict = book.to_dict()
            #If this book exists
            if book:
                #loop through shelves to see if book is in any
                shelves = Shelf.query().fetch()
                for shelf in shelves:
                    #If book is in a shelf, remove it
                    if(shelf.book == id):
                        shelf.book = ""
                        shelf.put()
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

    def put(self, id):

        book = ndb.Key(urlsafe=id).get()
        book_data = json.loads(self.request.body)
        if 'title' in book_data:
            book.title = book_data['title']
        if 'author' in book_data:
            book.author = book_data['author']
        if 'language' in book_data:
            book.language = book_data['language']
        if 'isbn' in book_data:
            book.isbn = book_data['isbn']

        book.put()
        book_dict = book.to_dict()
        book_dict['self'] = '/books/' + book.key.urlsafe()
        book_dict['book_id'] = book.key.urlsafe()
        self.response.write(json.dumps(book_dict))



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
                    genre=shelf_data['genre'],
                    number=shelf_data['number'],
                    wood=shelf_data['wood'],
                    book='')
        shelf.put()
        shelf_dict = shelf.to_dict()
        shelf_dict['self'] = '/shelves/' + shelf.key.urlsafe()
        shelf_dict['shelf_id'] = shelf.key.urlsafe()
        self.response.write(json.dumps(shelf_dict))

    def delete(self, id):
        if id:
            shelf = ndb.Key(urlsafe=id).get()
            if shelf:
                shelf_dict = shelf.to_dict()
                #handle book in shelf here
                if(shelf_dict['book'] != ''):
                    book_id = shelf_dict['book']
                    book = ndb.Key(urlsafe=book_id).get()
                    book.shelf = ''
                    book.put()
                shelf.key.delete()
                response = {"Result":204, "Message":"Shelf deleted"}
                self.response.write(json.dumps(response))
            else:
                response = {"Result":403, "Message":"Error: Shelf not found"}
                self.response.status = 403
                self.response.write(json.dumps(response))

        else:
            response ={"Result":403, "Message":"Error: Shelf not found"}
            self.response.status = 403
            self.response.write(json.dumps(response))

    def put(self, id):
        shelf = ndb.Key(urlsafe=id).get()
        shelf_data = json.loads(self.request.body)
        if 'number' in shelf_data:
            shelf.number = shelf_data['number']
        if 'genre' in shelf_data:
            shelf.genre = shelf_data['genre']
        if 'wood' in shelf_data:
            shelf.wood = shelf_data['wood']
        if 'room' in shelf_data:
            shelf.room = shelf_data['room']

        shelf.put()
        shelf_dict = shelf.to_dict()
        shelf_dict['self'] = '/shelves/' + shelf.key.urlsafe()
        shelf_dict['shelf_id'] = shelf.key.urlsafe()
        self.response.write(json.dumps(shelf_dict))

class BookInShelfHandler(webapp2.RequestHandler):

    def get(self, id):

        shelf = ndb.Key(urlsafe=id).get()
        shelf_dict = shelf.to_dict()
        book_id = shelf_dict['book']
        book = ndb.Key(urlsafe=book_id).get()

        if book:
            book_dict = book.to_dict()
            book_dict['self'] = '/books/' + book.key.urlsafe()
            book_dict['book_id'] = book.key.urlsafe()
            self.response.write(json.dumps(boat_dict))
        else:
            response ={"Result":405, "Message":"Error: No book in shelf"}
            self.response.status = 405
            self.response.write(json.dumps(response))


class StoreHandler(webapp2.RequestHandler):

    def put(self, id):
        body = json.loads(self.request.body)
        book_id = body['book']

        book = ndb.Key(urlsafe=book_id).get()
        shelf = ndb.Key(urlsafe=id).get()
        shelf_dict = shelf.to_dict()

        if shelf:
            if book:
                current_book_id = shelf_dict['book']
                if (current_book_id != ''):
                    current_book = ndb.Key(urlsafe=current_book_id).get()
                    current_book.shelf = ''
                    current_book.put()
                book.shelf = id
                shelf.book = book_id
                book.put()
                shelf.put()
                shelf_dict = shelf.to_dict()
                shelf_dict['self'] = '/shelves/' + shelf.key.urlsafe()
                shelf_dict['shelf_id'] = shelf.key.urlsafe()
                self.response.write(json.dumps(shelf_dict))

    def delete(self, id):
        shelf = ndb.Key(urlsafe=id).get()
        if shelf:
            shelf_dict = shelf.to_dict()
            book_id = shelf_dict['book']
            book = ndb.Key(urlsafe=book_id).get()
            shelf.book = ''
            book.shelf = ''
            book.put()
            shelf.put()
            response = {"Result":204, "Message":"Book removed from shelf"}
            self.response.write(json.dumps(response))

        else:
            response ={"Result":403, "Message":"Error: Please provide a valid shelf id"}
            self.response.status = 403
            self.response.write(json.dumps(response))

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.write("Hello, final project")

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/books', BookHandler),
    ('/books/(.*)', BookHandler),
    ('/shelves', ShelfHandler),
    ('/shelves/(.*)/store', StoreHandler),
    ('/shelves/(.*)/book', BookInShelfHandler),
    ('/shelves/(.*)', ShelfHandler)

], debug=True)
