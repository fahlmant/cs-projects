#!/usr/bin/python
import socket
import sys

def valid_error():
    print('Please provide a valid port number')
    sys.exit(0)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
if (len(sys.argv) > 1):
    if (int(sys.argv[1]) > 0):
        port = int(sys.argv[1])
    else:
        valid_error()
else:
    valid_error()

s.bind(("", port))

while 1:
    print "Hello"

