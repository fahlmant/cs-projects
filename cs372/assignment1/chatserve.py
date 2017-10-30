#!/usr/bin/python
import socket
import sys

def valid_port_error():
    print('Please provide a valid port number')
    sys.exit(0)


def connect_to_client(sock, handle):
    clienthandle = sock.recv(1024)
    sock.send(handle)
    return clienthandle

def message_loop(sock, clienthandle, handle):
    message_send = '' 
    while 1:
        message_recv = sock.recv(500)
        if message_recv == '':
            print "Connection with client terminated"
            break
        print handle + "> " + message_recv
        while len(message_send) > 500 or len(message_send) == 0:
            message_send = raw_input(handle + "> ")
        if message_send == "\quit":
            print "Connection to client terminated"
            break
        sock.send(mssage_send)
        

if __name__ == "__main__":

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    if (len(sys.argv) > 1):
        if (int(sys.argv[1]) > 0):
            port = int(sys.argv[1])
        else:
            valid_port_error()
    else:
        valid_port_error()

    handle = ""
    while len(handle) > 10 or len(handle) == 0:
        handle = raw_input("Enter a handle: ")
    s.bind(("", port))
    s.listen(1)
    print handle + ">"
    while 1:
        sock, address = s.accept()
        clienthandle = connection_to_client(sock, handle)
        message_loop(sock, clienthandle, handle)
        sock.close()


