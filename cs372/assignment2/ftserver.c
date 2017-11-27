/****
 *Taylor Fahlman
 *CS 372, Section 400
 *Assignment 2
 *Citations in README
**/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <dirent.h>

//Removes spaces from buffers with extra spaces, from stackoverflow:
//
void remove_spaces(char *my_string) {

    char *i = my_string;
    char *j = my_string;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ') {
            i++;
        }
    }
    *i = 0;
}

//Connects to the data port and returns the file desc.
int get_data_port_fd(char* ip, char* port) {

    //Beej's guide to fill out addrinfo structs
    struct addrinfo hints, *res;
    int result;

    //More Beej's guide, set the type of port and protocol (ipv4 and tcp)
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(ip, port, &hints, &res);

    //Create socket, a la Beej's
    int client_data_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(client_data_fd == -1) {
        printf("Connection to client data port failed, aborting\n");
        exit(1);
    }

    //Connect to data port on client and return file descriptor
    result = connect(client_data_fd, res->ai_addr, res->ai_addrlen); 
    return client_data_fd;
    
}

int list_dir(char **file_list) {

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int num_files = 0;
    int i = 0;
    if(d) {
        while ((dir = readdir(d)) != NULL) {
                file_list[i] = dir->d_name;
                i++;
        }
    }
    return i;
}

//Ensures file exists, then sends it to client 
void send_file(int conn_fd, int data_fd, char* file_name) {

    //First, check if file exists
    int i = 0;
    int exists = 0;
    char *file_list[100];
    int num_files = list_dir(file_list);
    //Loops through all files in directory to see if the file exists
    for(i = 0; i < num_files; i++) {
        if(strcmp(file_list[i], file_name) == 0) {
            exists = 1;
        }
    }

    if(exists == 1) {
        char file_buffer[1000];
        memset(file_buffer, 0, sizeof(file_buffer));
        int file_fd = open(file_name, O_RDONLY);
    	while (1) {
	    	int bytes_read = read(file_fd, file_buffer, sizeof(file_buffer)-1);
		    if (bytes_read == 0) // We're done reading from the file
			    break;

    		if (bytes_read < 0) {
	    		printf("Error reading file\n");
		    	return;
    		}
            send(data_fd, file_buffer, sizeof(file_buffer) - 1, 0);
   
    	}
    }
    else {
        printf("The requested file does not exist\n");
    }

}

//List and send the current directory to the client
void send_dir(int conn_fd, int data_fd) {

    //Leaving for reference purpose
    /*
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int num_files = 0;
    if(d) {
        while ((dir = readdir(d)) != NULL) {
            //For each file in the directory, send it and a newline to client 
            send(data_fd, dir->d_name, strlen(dir->d_name), 0);
            send(data_fd, "\n", strlen("\n"), 0);
        }
    }*/

    int i = 0;
    char *file_list[100];

    //Get list of all files in directory
    int num_files = list_dir(file_list);
    for (i = 0; i < num_files; i++){
        send(data_fd, file_list[i], strlen(file_list[i]), 0);
        send(data_fd, "\n", strlen("\n"), 0);
    }
}

//Function to handle data and request from client
void handle_request(int client_fd) {

    //Set up buffers for client IP, port, command and filename
    char client_ip[100];
    memset(client_ip, 0, sizeof(client_ip));
    char client_command[100];
    memset(client_command, 0, sizeof(client_command));
    char client_data_port[100];
    memset(client_data_port, 0, sizeof(client_data_port));
    char client_file_req[100];
    memset(client_file_req, 0, sizeof(client_file_req));


    printf("Receiving command from client\n");

    //Recieves IP into IP buffer
    recv(client_fd, client_ip, sizeof(client_ip)-1, 0);
    printf("Recieved IP: %s\n", client_ip);
    
    //Recieves command into command
    recv(client_fd, client_command, sizeof(client_command)-1, 0);
    printf("Recieved Command: %s\n", client_command);
    
    //If the command is -g, receive filename into filename buffer
    if(strstr(client_command, "-g")) {
        recv(client_fd, client_file_req, sizeof(client_file_req)-1, 0);
        printf("Recieved file requested: %s\n", client_file_req);
        remove_spaces(client_file_req);
        //From stackoverflow, removes newline:
        //
        strtok(client_file_req, "\n");
    }

    //Receive data port into data port buffer
    recv(client_fd, client_data_port, sizeof(client_data_port)-1, 0);
    printf("Recieved data port: %s\n", client_data_port);
    //Ensure that the server and client both are at the same place by sleeping
    sleep(2);
  
    //Since buffers are 100 bytes, stripes all the spaces that the client appends
    remove_spaces(client_ip);
    remove_spaces(client_data_port);

    //Connect to the data port
    int data_port_fd = get_data_port_fd(client_ip, client_data_port);
    
    //Either list directory or get file depending on command, or ask for valid command
    if(strstr(client_command, "-l")) {
        printf("Sending directory list\n");
        send_dir(client_fd, data_port_fd);
    }
    else if(strstr(client_command, "-g")) {
        printf("Attempting to send file %s\n", client_file_req);
        send_file(client_fd, data_port_fd, client_file_req);
    }
    else {
        printf("Please provide a valid option\n");
    }

    //Close the data port now that we're done with it
    close(data_port_fd);
    
}

//Idle until a client connects
void wait_for_connection(int fd) {

    //Need a file descriptor, socakddr_storage and socklen_t for client
    int client_fd;
    struct sockaddr_storage client_addr;
    socklen_t addr_len;

    //Loop until a client connect
    while(1) {
        //Accept the client's control connection, handle the case where doesn't succeed
        addr_len = sizeof(client_addr);
        client_fd = accept(fd, (struct sockaddr *)&client_addr, &addr_len);
        if(client_fd == -1) {
            continue;
        }

        //Hanle request for client then close connection
        printf("Client connection initated\n");
        handle_request(client_fd);
        close(client_fd);
        printf("Connection closed\n");
    }
}

//Initate socket to serve the control communication
int startup(char *port) {
   
    //Use Beej's guide to fill out addrinfo structs
    struct addrinfo hints, *res;
    int result; 

    //More Beej's guide, set the type of port and protocol (ipv4 and tcp)
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    //Get the nessesary information to connect to the port
    getaddrinfo(NULL, port, &hints, &res);

    //Actually create the socket, exit on failure
    int fd = socket(hints.ai_family, hints.ai_socktype, 0);
    if(fd == -1) {
        printf("Socket failed, are you sure the port is available?\n");
        exit(1);
    }
    //Bind to the socket using info from getaddrinfo, exit on failure
    result = bind(fd, res->ai_addr, res->ai_addrlen);
    if(result == -1) {
        printf("Bind failed\n");
        exit(1);
    }
    //Start listening on socket, use a backlog of 5 (arbitrary since we have one connection)
    //Exit on failure
    result = listen(fd, 5);
    if(result == -1) {
        printf("Listen failed\n");
        exit(1);
    }
    //If creation, binding and listening succeed, retrun file desrcriptor of control socket
    return fd;
}

int main(int argc, char** argv) {

    //Ensure there is a port, and only use the first argument
    if (argc < 2) {
        printf("Please provide a valid port number\n");
        exit(1);
    }
    if (argc > 2) {
        printf("See more than one argument, only using the first\n");
    }
  
    //Get socket set up on port provided by command line
    int fd = startup(argv[1]);
    printf("Listening on port %s\n", argv[1]);
    //Idle until client and handle 
    wait_for_connection(fd);
    return 0;
}
