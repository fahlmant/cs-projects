#!/usr/bin/python
import socket
import sys

#Function prints missing port number error and exits if user doesn't provide port.
def valid_port_error():
    print('Please provide a valid port number')
    sys.exit(0)

#Connects to client by receiving the client's handle, then sending the server's handle.
def connect_to_client(sock, handle):
    clienthandle = sock.recv(1024)
    sock.send(handle)
    return clienthandle

#Loops repeatedly once the handshake between the client and server is done
#and handles message sneding and recieving
def message_loop(sock, clienthandle, handle):
    message_send = '' 
    while 1:
        #Recieves up to 500 bytes from the client
        message_recv = sock.recv(500)
        #If the client sends nothing, the connection is terminated
        if message_recv == '':
            print "Connection with client terminated"
            break
        #Prints out the message recieved from client
        print clienthandle + "> " + message_recv
        #Takes input from terminal, from 0 to 500 bytes
        while len(message_send) > 500 or len(message_send) == 0:
            message_send = raw_input(handle + "> ")
        #If the message is "\quit", then terminate the connection
        if message_send == "\quit":
            print "Connection to client terminated"
            break
        #Send the message
        sock.send(mssage_send)
        

if __name__ == "__main__":

    #Create a TCP socket with the Sockets API
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #Ensure that a port is given to the program and that its a valid number
    if (len(sys.argv) > 1):
        if (int(sys.argv[1]) > 0):
            port = int(sys.argv[1])
        else:
            valid_port_error()
    else:
        valid_port_error()

    handle = ""
    #Ask for handle from user, up to 10 characters
    while len(handle) > 10 or len(handle) == 0:
        handle = raw_input("Enter a handle: ")
    #Bind socket to port and start listening for incomming connections
    s.bind(("", port))
    s.listen(1)
    print handle + ">"
    #For any new connection, accept it, get the clienthandle, and start message loop until user closes program
    while 1:
        sock, address = s.accept()
        clienthandle = connection_to_client(sock, handle)
        message_loop(sock, clienthandle, handle)
        sock.close()


