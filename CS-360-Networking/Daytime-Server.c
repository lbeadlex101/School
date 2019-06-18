//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #1
// Day-Time Server: This program acts as the server to listen for a connection,
// receive a connection, and echo the date and time to the client. 
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h> 

#define SERVER_PORT 5421 // lbea port #: 5421
#define MAX_PENDING 5
#define MAX_LINE 256 

int main() 
{

  	struct sockaddr_in sin;
  	char buf[MAX_LINE];
  	int len;
  	socklen_t new_len;
  	int s, new_s;

	// Time data structure 	
	struct tm* tm_obj;
	time_t currentTime;
	time(&currentTime);
	tm_obj = localtime(&currentTime);
  
	// Address data structure
  	bzero((char *) &sin, sizeof(sin));
  	sin.sin_family = AF_INET;
  	sin.sin_addr.s_addr = INADDR_ANY;
  	sin.sin_port = htons(SERVER_PORT);

  	// Passive open
  	if (( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  	{
    	printf("socket call failed");
    	exit(1);
  	}
  
  	if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
  	{
    	printf("bind call failed");
    	exit(1);
  	}

  	listen(s, MAX_PENDING);

  	// Infinite loop to wait for a connection
  	while (1)
  	{
    	if (( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
		{
      		printf("accept call failed");
      		exit(1);
    	}
    
        // Zero the buffer and receive null byte from client	
       	bzero(buf, sizeof(buf));
       	recv(s, buf, sizeof(buf), 0);

	// Zero the buffer, store date and time in buffer, send 
	// buffer to the client, and close socket used for 
	// sending
    	bzero(buf, sizeof(buf));
    	strftime(buf, sizeof(buf),"%c",tm_obj);
		send(new_s,buf,sizeof(buf), 0);
    	close (new_s);
 	}

	return 0;
	
}
