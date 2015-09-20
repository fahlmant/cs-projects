#Name: Taylor Fahlman
#Email: fahlmant@onid.oregonstate.edu
#Class: CS344-001
#Assignment: 1
#Resources:man cal, https://docs.python.org/2/library/subprocess.html
#Extra credit attempted
import sys
import subprocess

#makes the command cal by default
command = "cal "

#if there are any other args, appends them onto the command string
for i in range(1, len(sys.argv)):
    command += str(sys.argv[i]).strip(',') + " " 

#calles the command using subprocess Popen
subprocess.Popen(command, shell=True)
