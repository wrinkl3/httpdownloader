#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

#define SIZEOF_REQUEST 1024
#define SIZEOF_RESPONSE 8162

//generic error message
void error(const char *err){ 
    perror(err); 
    exit(0); 
}

//checks the given line for links
void check_for_links(char *line){
	int i, size;
	size = strlen(line);
	for(i = 0; i<size; i++){
		if(strncmp(line+i, "href", 4) == 0){

		}
	} 
}

void parse_response(char *response){	//TODO: write to file here
	//discard the metadata
	char buff[sizeof(response)], *tok;
	tok = strtok(response, "\n");
	while(tok != NULL){		//go through the tokens until the html begins
		printf("%s\n", tok);
		if(strncmp("<!", tok, 2) == 0)	
			break;
		tok = strtok(NULL, "\n");
	}
	//now for the file
	strcpy(buff, "");	//init the buffer
	while( tok != NULL){
		check_for_links(tok);
		strcat(buff, tok);
		strcat(buff, "\n");
		strtok(NULL, "\n");
	}
}

//uses an existing socket connection to download the http file
char *download_http(char *file_addr, char *host, int sockfd){
	char request[SIZEOF_REQUEST+1], response[SIZEOF_RESPONSE+1], *r_template;
	r_template = "GET / HTTP/1.0\r\n"
    "Host: %s\r\n"
    "User-Agent: HttpDownloader\r\n" 
    "\r\n";

    sprintf(request, r_template, host);

    printf("Request:\n%s\n",request);

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
    }

    // receive the response
    memset(response,'\0', SIZEOF_RESPONSE);
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
    }
    if (received >= total)
        error("can't store complete response from socket");

    //print
    //printf("Response:\n%s",response);
    parse_response(response);
    return r_template;
}