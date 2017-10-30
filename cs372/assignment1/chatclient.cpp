/****
 *Taylor Fahlman
 * CS 372, Section 400
 * Assignment 1
 * Source: http://www.geeksforgeeks.org/socket-programming-cc/
 * http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 * https://github.com/angrave/SystemProgramming/wiki/Networking,-Part-2:-Using-getaddrinfo
 * https://stackoverflow.com/questions/7352099/stdstring-to-char
 * */
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

//Makes the socket to connect to the server
int make_socket() {

    //Declare variables
    int fd;
    int result;

    //Create a TCP socket using the Sockets API and abort if the socket isn't created
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("Error making socket, aborting\n");
        exit(1);
    }

    return fd;
}

//Initializes connection from client to server
void init_connection_socket(int fd, struct sockaddr_in *addr ) {

    //Uses connect() call from sockets, passing the file descriptor,
    //address and address length
//    int result = connect(fd, addr->ai_addr, addr->ai_addrlen);
    int result = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(result == -1) {
        printf("Error connecting, aborting\n");
        exit(1);
    }
}

//Performs initial handshake of exchanging handles from client to server
void connect_to_server(int fd, char* handle, char* serverhandle) {

    //send handle to the server via the socket
    int status = send(fd, handle, strlen(handle), 0);
    //Recieve up to 10 characters from the server, which is the server handle
    recv(fd, serverhandle, 10, 0);
}

//Loop over sending and recieving messages from server
void message_loop(int fd, char* handle, char* serverhandle) {

    //Create buffers for messages, zero them out, and initialize other variables
    char message_to_send[500];
    char message_to_recv[500];
    int sent_bytes;
    int recv_bytes;
    memset(message_to_send, 0, sizeof(message_to_send));
    memset(message_to_recv, 0, sizeof(message_to_recv));

    //Start loop
    while(1) {
        //Prompt user for message to send
        printf("%s> ", handle);
        fgets(message_to_send, 501, stdin);
        //If the user enters "\quit", gracefully close the program
        if(strcmp(message_to_send, "\\quit\n") == 0){
            exit(0);
        }
        //Send message that user gave to the server over the file descriptor.
        sent_bytes = send(fd, message_to_send, strlen(message_to_send), 0);
        if(sent_bytes == -1) {
            printf("Error in communications with client\n");
            exit(1);
        }
        //Wait and recieve message from server
        recv_bytes = recv(fd, message_to_recv, 501, 0);
        //If the status of the recieving is -1, abort
        if(recv_bytes == -1){
            printf("Error in recieving communication\n");
            exit(1);
        }
        //If the server sends nothing, the server must have \quit, so close
        else if(recv_bytes == 0) {
            printf("Connection terminated\n");
            exit(0);
        }
        //Otherwise, print out whatever the server sent us.
        else {
            printf("%s> %s\n", serverhandle, message_to_recv);
        }
    
        //Ensure that buffers are zeroed out before next loop
        memset(message_to_send, 0, sizeof(message_to_send));
        memset(message_to_recv, 0, sizeof(message_to_recv));
   }
}

//Prompt user for handle, and store it in a char* variable
void get_handle(char *handle) {
    printf("Enter a handle: ");
    scanf("%s", handle);
}

int main(int argc, char** argv) {

    //Ensure both a hostname and port are provided
    if (argc != 3) {
        printf("Please provide a hostname and port number to connect to\n");
        exit(1);
    }

    //Declare file descriptors, variables for handles
    int fd;
    char handle[10];
    char serverhandle[10];

    //Declare addrinfo structs, feed in both hostname and port. 
    struct addrinfo hints, *addr_info;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(server_addr.sin_family, argv[1], &server_addr.sin_addr);
//    int result = getaddrinfo(argv[1], argv[2], &hints, &addr_info);

    //Get te handle from the user
    get_handle(handle);
    //Create socket
    fd = make_socket();
    //Connect socket to server
    init_connection_socket(fd, &server_addr);
    //Handshake, and exchange handles
    connect_to_server(fd, handle, serverhandle);
    //Loop sending and recieving messages until user quits. 
    message_loop(fd, handle, serverhandle);

    return 0;
}



