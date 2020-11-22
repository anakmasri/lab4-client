#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //inet_addr


void func(int sock_desc){

    char buff[80];
    int n;

    for (;;){
        bzero(buff, sizeof(buff));
        printf("Enter message : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');

        write(sock_desc, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sock_desc, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}


int main(){

    int sock_desc, connfd;
    struct sockaddr_in server, client;

    //socket create and varification
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1){
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

	bzero(&server, sizeof(server));


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.1.104"); //ip address server
    server.sin_port = htons(8888);

    //connect client socket to server socket
    if(connect(sock_desc, (struct sockaddr *)&server, sizeof(server)) != 0){
        printf("connection with server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    //funcfor chat
    func(sock_desc);

    //close the socket
    close(sock_desc);
}
