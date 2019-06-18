//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #2
// Magic 8 Ball Client :
// This program implements the Magic 8 ball protocol between a server and
// client. 
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <stdlib.h> 
#include <unistd.h>
#include <stdbool.h>
#include <string.h> 

#define SERVER_PORT 5421
#define MAX_LINE 36
//-----------------------------------------------------------------------------
// Function Declarations: 
void writeError(const char* error);
bool isSane(const char* buffer);
//-----------------------------------------------------------------------------
// Main Driver:
int main(int argc, char * argv[]) 
{
	char *host;
  	char buf[MAX_LINE];
  	int s;
  	int len;
	struct hostent *hp;
  	struct sockaddr_in sin;
  
  	if (argc == 2) 
  	{
    	host = argv[1];
  	}
  
  	else
  	{
    	fprintf(stderr, "Simplex-talk host\n");
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
    	writeError("socket call failed");
    	exit(1);
  	}

 	// Establish host connection
  	if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
  	{
    	writeError("connect call failed");
    	close(s);
    	exit(1);
  	}

    // Clear buffer and set first type code
    bzero(buf, sizeof(buf));
    buf[0] = '1';
    buf[1] = '0';
    
    // Initiate Connection to Server
    char start[20] = "Hello Magic 8 Ball\n";
    int sizeofStart = strlen(start);
    char sizeOne = (sizeofStart / 10) + '0';
    char sizeTwo = (sizeofStart % 10) + '0';
    
    buf[2] = sizeOne;	// Payload Size byte Index 2
    buf[3] = sizeTwo;	// Payload Size byte Index 3
    
    strlcat(buf, start, sizeof(buf));
    
    send(s, buf, sizeof(buf), 0);
    recv(s, buf, sizeof(buf), 0);
    
    if (isSane(buf) == false)
	{
    	writeError("Protocol Violation: Sanity Test Failed");
    	
        bzero(buf, sizeof(buf));
        buf[0] = 5 + '0';
        buf[1] = '0';
        
        char* msg = "Protocol Violation: Sanity Test Failed";
        int msgLength = strlen(msg);
        
        char sizeOne = (msgLength / 10) + '0';
        char sizeTwo = (msgLength % 10) + '0';
        buf[2] = sizeOne;	// Payload Size byte Index 2
        buf[3] = sizeTwo;	// Payload Size byte Index 3
        
        strlcat(buf, msg, sizeof(buf));
        send(s, buf, sizeof(buf), 0);
        
        exit(1);
	}

    if (buf[0] == '2')
	{
        bzero(buf, sizeof(buf));
        buf[0] = '3';
        buf[1] = '0';
        
        // Prompt client for input and receive
        fputs("Please ask your question.\n", stdout);
        char inputStr[32];
        scanf("%s", inputStr);
        int sizeOfInput = strlen(inputStr);
        
        sizeOne = (sizeOfInput / 10) + '0';
        sizeTwo = (sizeOfInput % 10) + '0';
        buf[2] = sizeOne;	// Payload Size byte Index 2
        buf[3] = sizeTwo;	// Payload Size byte Index 3
        
        strlcat(buf, inputStr, sizeof(buf));
        send(s, buf, sizeof(buf), 0);
    } 
    
	else
	{
        fputs("Protocol Violation: Code != 20", stdout);
        close(s);
    }
    
    recv(s, buf, sizeof(buf), 0);
    
	if (isSane(buf) == false)
	{
    	writeError("Protocol Violation: Switch Sanity Test Fail");
    	
        bzero(buf, sizeof(buf));
        buf[0] = 5 + '0';
        buf[1] = '0';
        
        char* msg = "Protocol Violation: Switch Sanity Test Fail";
        int msgLength = strlen(msg);
        
        char sizeOne = (msgLength / 10) + '0';
        char sizeTwo = (msgLength % 10) + '0';
        buf[2] = sizeOne;	// Payload Size byte Index 2
        buf[3] = sizeTwo;	// Payload Size byte Index 3
        
        strlcat(buf, msg, sizeof(buf));
        send(s, buf, sizeof(buf), 0);
        
        exit(1);
	}
   
    if (buf[0] == '4')
	{
        char messageReceived[32];
        int newSize = 0;
        int i = 4;
        int j = 0;
        
		for (i = 4; (i < MAX_LINE) && (buf[i] !='\0'); i++)
		{
            messageReceived[j] = buf[i];
            newSize = j+1;
            j = j + 1;
        }
        
        messageReceived[newSize] = '\0';
        fputs(messageReceived, stdout);
    }
    
    else
	{

		fputs("Protocol Violation: Code != 40", stdout);
		close(s);
    }
	 
    close(s);
    
	return 0;
}
//-------------------------------------------------------------------
// Error Output Function:
void writeError(const char* error)
{

	fputs(error, stdout);

}
// ------------------------------------------------------------------
// Sanity Check: 
// Check to validate the payload length matchs the declared length.
bool isSane(const char* buffer)
{

	int firstSize = buffer[2] - '0'; // Payload Length byte position 2
	int secondSize = buffer[3] - '0'; // Payload Length byte position 3
	int size = (firstSize * 10) + secondSize;
	
	if( (size + 4) == strlen(buffer) )
	{
		return true;
	}
	
	else
	{
		return false; 
	}

}
//-------------------------------------------------------------------

