#Name: Taylor Fahlman
#Email: falmant@onid.oregonstate.edu
#pClass: CS344
#Assignment: 1
#Resources: https://docs.python.org/2/library/os.html, https://docs.python.org/2/library/os.path.html, 
#https://docs.python.org/2/library/getopt.html

import os
import sys
import getopt

#Function that checks if a path exists, and recursively creates the path if it does not
def create_path(root, term, current_class, dir_name):
    path = root + "/" + term + "/" + current_class + "/" + dir_name
    if(os.path.exists(path) is False):
        os.makedirs(path)
    else:
        print "This directory already exists!"
#function that checks if a path exists, and create a symbolic link if it doesn't
def create_link(file_name, term_link, class_link, target_file):
    if(os.path.exists(file_name) is False):
        os.symlink("/usr/local/classes/eecs/" + term_link + "/" + class_link + "/" + target_file, file_name)
    else:
        print "This link already exists!"

#Gets the current directory
root_dir = os.getcwd()

#gets the command line args
cmd_line = sys.argv[1:]

#parse the command line args using get opt
args = getopt.getopt(cmd_line,"t:c:",["term=","class="])

#finds the command line args and their values
for i in range(len(args)):
    for j in range(len(args[i])):
        for k in range (len(args[i][j])):
            if (args[i][j][k] == '-t' or args[i][j][k] == '--term'):
                term_name = args[i][j][k+1]
            if (args[i][j][k] == '-c' or args[i][j][k] == '-class'):
                class_name = args[i][j][k+1]


#creates all needed dirs using the term and class from command line args
create_path(root_dir, term_name, class_name, "assignments")
create_path(root_dir, term_name, class_name, "examples")
create_path(root_dir, term_name, class_name, "exams")
create_path(root_dir, term_name, class_name, "lecture_notes")
create_path(root_dir, term_name, class_name, "submissions")

#Checks if the symbolic links exist, creates them if they dont
readme = root_dir + "/README"
src_class = root_dir + "/src_class"

create_link(readme, term_name, class_name, "/README")
create_link(src_class, term_name, class_name, "/src")


