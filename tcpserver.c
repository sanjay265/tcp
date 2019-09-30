#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MAX 80
void func(int clientsocket) 
{ 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        fread(clientsocket, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        fwrite(clientsocket, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 

int main()
{
	char servermsg[256]="connected";
	int serversocket;
	serversocket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	
	//bind the socket
	bind(serversocket, (struct sockaddr *)&server_address,sizeof(server_address));
	
	listen(serversocket,5);	
	int clientsocket;
	clientsocket=accept(serversocket,NULL,NULL);	
	send(clientsocket,servermsg,sizeof(servermsg),0);	
				

	//recv(networksocket,&server_response,sizeof(server_response),0);
	
	//printf("The response is: %s\n",server_response);
	return 0;


}
