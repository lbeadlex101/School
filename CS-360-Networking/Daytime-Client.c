//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #1
// Day-Time Client: This program acts as the client to send a connection to the 
// server, and receive the date and time from the server.  
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <stdlib.h> 
#include <unistd.h>
#include <string.h> 

#define SERVER_PORT 5421 // lbea port #: 5421
#define MAX_LINE 256

int main(int argc, char * argv[]) 
{

	struct hostent *hp;
  	struct sockaddr_in sin;
  	char *host;
  	char buf[MAX_LINE];
  	int s;
  	int len;
  
  	if (argc==2) 
  	{
    	host = argv[1];
  	}
  
  	else
  	{
    	fprintf(stderr, "usage: simplex-talk host\n LOCALHOST???");
	
    	exit(1);
  	}
  
  	// Invokation Resolver - translates the name to the IP address 
  	hp = gethostbyname(host);
  
  	if (!hp)
  	{
    	fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    	exit(1);
  	}

  	// Address data structure
  	bzero((char *)&sin, sizeof(sin));
  	sin.sin_family = AF_INET;
  	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  	sin.sin_port = htons(SERVER_PORT);

  	// Active open
  	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  	{
    	printf("socket call failed");
    	exit(1);
  	}

  	// Establish host connection
  	if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
  	{
    	printf("connect call failed");
    	close(s);
    	exit(1);
  	}

  	// Clear the buffer and send a null byte to the server
    bzero(buf, sizeof(buf));
    send(s, buf, sizeof(buf), 0);
    
    // Receive a connection from the server and print 
    // date and time. 
    recv(s, buf, sizeof(buf), 0);  
	fputs(buf, stdout);

  	return 0;
  
}
