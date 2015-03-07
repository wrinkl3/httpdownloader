#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "DownloadManager.h"

#define PORT 80


//setup the connection and download stuff
void connect_and_download(char *host){
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //create the socket
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("can't open the socket");

    //look up the address
    server = gethostbyname(host);
    if (server == NULL) 
        error("ERROR, no such host");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    // connect the socket
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("can't connect");
    //recursively download the website
    download_http(host, host, sockfd);
    //close the connection
    close(sockfd);
}



int main(int argc,char *argv[]){
    //parse arguments
    if(argc<3){
        printf("insufficient number of arguments\n");
        return -1;
    }
    char *host, *dir;
    host = argv[1];
    dir = argv[2];
    //initiate the connection
    connect_and_download(host);

    return 0;
}