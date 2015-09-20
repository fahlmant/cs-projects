#Name: Taylor Fahlman
#Email: fahlmant@onid.oregonstate.edu
#Class: CS344-001
#Assignment: 1
#Resources:docs.python.org/2/library/urllib2.html,q

#tutorialspoint.com/python/python_command_line_arguments.htm


import urllib2
import sys

#Gets the name of the website from arguments, appends the http to the front
#and puts it in the url variable
url = "http://" + sys.argv[1]


#sets the file variable to the name given in the arguments
file_name = sys.argv[2]

#opens a new file with the filename give, and the arguments to write 
# and overwrite if the file exists alread
output_file = open(file_name, 'w')

#opens the url, saves html info in the url_info variable
url_info= urllib2.urlopen(url)

#Writes the html from url info the the file
output_file.write(url_info.read())


