//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #2
// Magic 8 Ball Client 
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

//-------------------------------------------------------------------
// Function Declarations: 
void writeError(const char* error);
bool isSane(const char* buffer);
//-------------------------------------------------------------------
// Main Driver:
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
    	fprintf(stderr, "Simplex-talk host\n");
    	exit(1);
  	}
  
  	hp = gethostbyname(host);
  
  	if (!hp)
  	{
    	fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    	exit(1);
  	}

  	bzero((char *)&sin, sizeof(sin));
  	sin.sin_family = AF_INET;
  	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  	sin.sin_port = htons(SERVER_PORT);

  	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  	{
    	writeError("socket call failed");
    	exit(1);
  	}

 
  	if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
  	{
    	writeError("connect call failed");
    	close(s);
    	exit(1);
  	}

    // Initiate Connection to Server
    bzero(buf, sizeof(buf));
    buf[0] = '1';
    buf[1] = '0';
    char start[20] = "Hello Magic 8 Ball\n";
    int sizeofStart = strlen(start);
    char first = (sizeofStart / 10) + '0';
    char second = (sizeofStart % 10) + '0';
    buf[2] = first;
    buf[3] = second;
    
    strlcat(buf, start, sizeof(buf));
    send(s, buf, sizeof(buf), 0);
    recv(s, buf, sizeof(buf), 0);
    if (isSane(buf) == false)
	{
    	writeError("Protocol Violation Detected! ");
        bzero(buf, sizeof(buf));
        buf[0] = 5 + '0';
        buf[1] = '0';
        char* msg = "Protocol Violation";
        int msgLength = strlen(msg);
        char first = (msgLength / 10) + '0';
        char second = (msgLength % 10) + '0';
        buf[2] = first;
        buf[3] = second;
        strlcat(buf, msg, sizeof(buf));
        send(s, buf, sizeof(buf), 0);
        exit(1);
	}

    if (buf[0] == '2')
	{
        bzero(buf, sizeof(buf));
        buf[0] = '3';
        buf[1] = '0';
        fputs("Please ask your question.\n", stdout);
        char inputStr[32];
        scanf("%s", inputStr);
        int sizeOfInput = strlen(inputStr);
        first = (sizeOfInput / 10) + '0';
        second = (sizeOfInput % 10) + '0';
        buf[2] = first;
        buf[3] = second;
        strlcat(buf, inputStr, sizeof(buf));
        send(s, buf, sizeof(buf), 0);
    } 
    
	else
	{
        fputs("Protocol Violation Detected! Closing..", stdout);
        close(s);
    }
    
    recv(s, buf, sizeof(buf), 0);
    
    if (isSane(buf) == false)
	{
    	writeError("Protocol Violation Detected! Closing..");
        bzero(buf, sizeof(buf));
        buf[0] = 5 + '0';
        buf[1] = '0';
        char* msg = "Protocol Violation";
        int msgLength = strlen(msg);
        char first = (msgLength / 10) + '0';
        char second = (msgLength % 10) + '0';
        buf[2] = first;
        buf[3] = second;
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

		fputs("Protocol Violation Detected! Closing..", stdout);
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
bool isSane(const char* buffer)
{

	int firstSize = buffer[2] - '0';
	int secondSize = buffer[3] - '0';
	int size = (firstSize * 10) + secondSize;
	return (size + 4) == strlen(buffer);

}
//-------------------------------------------------------------------

