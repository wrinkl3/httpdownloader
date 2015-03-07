/#include <stdio.h>
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
#define SIZEOF_REQUEST 1024
#define SIZEOF_RESPONSE 8162


int main(int argc,char *argv[]){
    //parse arguments
    if(argc<3){
        printf("insufficient number of arguments\n");
        return -1;
    }
    char *host, *r_template, *dir;
    host = argv[1];
    dir = argv[2];
    //set the request template
/*    r_template = "GET / HTTP/1.0\r\n"
    "Host: %s\r\n"
    "User-Agent: HttpDownloader\r\n" 
    "\r\n";
*/
    struct sockaddr_in serv_addr;
    struct hostent *server;
//  char request[SIZEOF_REQUEST+1], response[SIZEOF_RESPONSE+1];

    //fill in the params
    
//  sprintf(request, r_template, host);
    //strcpy(request, request_fmt);
//  printf("request:\n%s\n",request);

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
    download_http(host, host, sockfd);
    

/*
    // send the request
    int bytes, sent, received, total;

    total = strlen(request);
    sent = 0;
    while (sent < total){
        bytes = write(sockfd,request+sent,total-sent);
        if (bytes < 0)
            error("can't send request");
        if (bytes == 0)
            break;
        sent+=bytes;
    };

    // receive the response
    memset(response,0, SIZEOF_RESPONSE);
    total = SIZEOF_RESPONSE;
    received = 0;
    while (received < total){
        bytes = read(sockfd,response+received,total-received);
        //printf("%d\n", bytes);
        if (bytes < 0)
            error("can't read response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
        if(received>=total)
            break;
    };
    if (received >= total)
        error("can't store complete response from socket");

    //close
    close(sockfd);

    //print
    printf("Response:\n%s",response);
*/  
    close(sockfd);
    return 0;
}