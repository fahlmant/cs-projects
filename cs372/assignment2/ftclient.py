#!/usr/bin/python
#Taylor Fahlman
#File Transfer Client
#CS 372, Assignment 2
import socket
import sys
import time


#Func to get IP to pass to server
#From https://stackoverflow.com/questions/24196932/how-can-i-get-the-ip-address-of-eth0-in-python
def get_ip_address():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.connect(("8.8.8.8", 80))
    ip = sock.getsockname()[0]
    sock.close()
    return ip



#Send client IP, data port, and command to server
def make_request(client_sock, ip):

    #Sleep between each send to ensure server receives data in right buffers

    #Easier to use a variable for the option
    option = sys.argv[3]

    #Ensure that 100 bytes get sent, including newline
    #(Tried to make this a function but ran into issue w/ getsizeof)
    while(sys.getsizeof(ip) < 99):
        ip += " "
    while(sys.getsizeof(option) < 99):
        option += " "

    print("Sending information")
    
    #Send IP and option since they're always in the same order
    client_sock.send(ip + '\n')
    time.sleep(1)
    client_sock.send(option + '\n')
    time.sleep(1)

    if '-g' in option:
        print('Requesting file ' + str(sys.argv[4]))
        #Get the file requested if option is -g, make it 100 bytes and send
        file_req = str(sys.argv[4])
        while(sys.getsizeof(file_req) < 99):
            file_req += " "
        client_sock.send(file_req + '\n')
        time.sleep(1)

        #Make sure data port is 100 bytes and send
        data_port = str(sys.argv[5])
        while(sys.getsizeof(data_port) < 99):
            data_port += " "
        client_sock.send(data_port)
        return sys.argv[5]
    #Since option already validated, we know this is -l
    else:
        print('Requesting directory list')
        #Get data port, make it 100 bytes and send it
        data_port = str(sys.argv[4])
        while(sys.getsizeof(data_port) < 99):
            data_port += " "
        client_sock.send(data_port)
        return sys.argv[4]

#def receive_dir_list():

#def receive_file():

def receive_response(s, data_port):
    
    option = sys.argv[3]
    #Set up data socket for data communications, listen for server connection
    data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    data_sock.bind(('', int(data_port)))
    data_sock.listen(1)

    #Accept server connection
    server_data_sock, addr = data_sock.accept()
    if option == '-g':
        printf('Receiving file ' + str(sys.argv[4]))
    else:
        printf('Receiving directory list')


#def proccess_arguments():

def initiate_contact():
    server = sys.argv[1]
    serve_port = int(sys.argv[2])
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server, serve_port))
    print("Connected to server")
    return s

if __name__ == "__main__":
#    proccess_arguments()
    ip = get_ip_address()
    s = initiate_contact()
    data_port = make_request(s, ip)
    receive_response(s, data_port)
