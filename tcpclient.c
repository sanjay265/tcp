#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAX 80

void func(int networksocket) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("client: "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        fwrite(networksocket, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        fread(networksocket, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 

int main()
{
	int networksocket;
	networksocket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	
	//CONNETION TO THE SERVER
	
		
	int connect_server=connect(networksocket, (struct sockaddr *)&server_address,sizeof(server_address));
	if(connect_server==-1){
	printf("There is an error connecting");
	}
	
	//receiving data from server
	
	char server_response[200];	
	recv(networksocket,&server_response,sizeof(server_response),0);
	printf("The response is: %s\n",server_response);
	
	func(networksocket);	

return 0;


}
