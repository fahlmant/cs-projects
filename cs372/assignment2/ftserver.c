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


void send_file(int conn_fd, int data_fd) {

}

void list_and_send_dir(int conn_fd, int data_fd) {

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int num_files = 0;
    if(d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
            num_files++;

        }
    }
}

void handle_request(int client_fd) {

    char client_data[1000];
    memset(client_data, 0, sizeof(client_data));


    char client_ip[99];
    memset(client_ip, 0, sizeof(client_ip));
    char client_command[99];
    memset(client_command, 0, sizeof(client_command));
    char client_data_port[99];
    memset(client_data_port, 0, sizeof(client_data_port));
    char client_file_req[99];
    memset(client_file_req, 0, sizeof(client_file_req));


    printf("Receiving command from client\n");
    recv(client_fd, client_ip, sizeof(client_ip)-1, 0);
    printf("Recieved IP: %s\n", client_ip);
    
    recv(client_fd, client_command, sizeof(client_command)-1, 0);
    printf("Recieved Command: %s\n", client_command);
    
    if(strstr(client_command, "-g") {
        recv(client_fd, client_file_req, sizeof(client_file_req)-1, 0);
        printf("Recieved file requested: %s\n", client_file_req);
    }

    recv(client_fd, client_data_port, sizeof(client_data_port)-1, 0);
    printf("Recieved data port: %s\n", client_data_port);
    sleep(2);
   

    
    
    if(strstr(client_command, "-l")) {
        printf("List\n");
        list_and_send_dir(client_fd, 0);
    }
    else if(strstr(client_data, "-g")) {
        printf("Get file\n");
    }
    else {
        printf("Please provide a valid option\n");
    }*/
    
/*
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
*/

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

    if (argc < 2) {
        printf("Please provide a valid port number\n");
        exit(1);
    }
    if (argc > 2) {
        printf("See more than one argument, only using the first\n");
    }
    //validate_port(argv);
  
    //Get socket set up on port provided by command line
    int fd = startup(argv[1]);
    printf("Listening on port %s\n", argv[1]);
    //Idle until client and handle 
    wait_for_connection(fd);
    return 0;
}
