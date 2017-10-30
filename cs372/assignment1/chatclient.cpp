#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>

int make_socket() {

    int fd;
    int result;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("Error making socket, aborting\n");
        exit(1);
    }

    return fd;
}


void init_connection_socket(int fd, struct addrinfo *addr ) {

    int result = connect(fd, addr->ai_addr, addr->ai_addrlen);
    if(result == -1) {
        printf("Error connecting, aborting\n");
        exit(1);
    }
}

void connect_to_server(int fd, char* handle, char* serverhandle) {

    
    int status = send(fd, handle, strlen(handle), 0);
    recv(fd, serverhandle, 10, 0);
}

void message_loop(int fd, char* handle, char* serverhandle) {

    char message_to_send[500];
    char message_to_recv[500];
    int sent_bytes;
    int recv_bytes;
    memset(message_to_send, 0, sizeof(message_to_send));
    memset(message_to_recv, 0, sizeof(message_to_recv));
    while(1) {
        printf("%s> ", handle);
        fgets(message_to_send, 501, stdin);
        if(strcmp(message_to_send, "\\quit\n") == 0){
            exit(0);
        }
        sent_bytes = send(fd, message_to_send, strlen(message_to_send), 0);
        if(sent_bytes == -1) {
            printf("Error in communications with client\n");
            exit(1);
        }
        recv_bytes = recv(fd, message_to_recv, 501, 0);
        if(recv_bytes == -1){
            printf("Error in recieving communication\n");
            exit(1);
        }
        else if(recv_bytes == 0) {
            printf("Connection terminated\n");
            exit(0);
        }
        else {
            printf("%s> %s\n", serverhandle, message_to_recv);
        }
    
        memset(message_to_send, 0, sizeof(message_to_send));
        memset(message_to_recv, 0, sizeof(message_to_recv));
   }
}

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
//    int result = getaddrinfo(argv[1], argv[2], &hints, &addr_info);

    get_handle(handle);
    fd = make_socket();
    init_connection_socket(fd, addr_info);
    connect_to_server(fd, handle, serverhandle);
    message_loop(fd, handle, serverhandle);

    return 0;
}



