//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #2
// Magic 8 Ball Server:
// This program implements the Magic 8 ball protocol between a server and
// client. 
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define SERVER_PORT 5421
#define MAX_PENDING 5
#define MAX_LINE 36 // Length of Payload Frame
//-----------------------------------------------------------------------------
// Function Declarations: 
void writeError(const char* error);
char* switchCase(int number);	
bool isSane(const char* buffer);
//-----------------------------------------------------------------------------
// Main Driver:
int main() 
{
	
	bool connected = false; 
	bool disconnect = false; 
	char buf[MAX_LINE];
	char msg[32];
    int s, new_s;
	int number = 0;
    int expecting = 0;
    int msgLength = 0;
    struct sockaddr_in sin;
	socklen_t new_len;
    
	// Address data structure
    bzero((char *) &sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
    
    // Passive Open
    if (( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
        writeError("socket call failed.");
        exit(1);
    }
    
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
	{
        writeError("bind call failed");
        exit(1);
    }
    
    listen(s, MAX_PENDING);
    
    // Infinite loop to wait for a connection with client
    while (1)
	{
    	if ( ( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
    			
		{
            writeError("accept call failed");
            exit(1);
        }
        
		connected = true; // Server is connected to Client
		expecting = 1;
        int flag = 0;
        
	    bzero(msg, sizeof(msg));
       
        while (connected == true)  // While Server is connected to client.
		{
            bzero(buf, sizeof(buf));
            recv(new_s, buf,sizeof(buf), 0);
            
            if (isSane(buf) == false)
			{
            	writeError("Sanity Check Failed on buf!");
                connected = false; // Connection guard break
                
				bzero(buf, sizeof(buf));
                buf[0] = 5 + '0';
                buf[1] = '0';
                
                char* msg = "Protocol Violation";
                int msgLength = strlen(msg);
                
                char sizeOne = (msgLength / 10) + '0';	
                char sizeTwo = (msgLength % 10) + '0';	
                buf[2] = sizeOne;	// Payload Size byte Index 2
                buf[3] = sizeTwo;	// Payload Size byte Index 3
                
                strlcat(buf, msg, sizeof(buf));
                send(new_s, buf, sizeof(buf), 0);
                
                exit(1);
			}
			
            if (expecting == 1)
			{
                if (buf[0] == '1')
				{
                    bzero(buf, sizeof(buf));
                    buf[0] = 2 + '0';
                    buf[1] = '0';
                   
				    strlcpy(msg,"Ask your question\n", sizeof(msg));
                    int msgLength = strlen(msg); 
                    
					char sizeOne = (msgLength / 10) + '0';
                    char sizeTwo = (msgLength % 10) + '0';
                    buf[2] = sizeOne;	// Payload Size byte Index 2
                    buf[3] = sizeTwo;	// Payload Size byte Index 3
                    
					strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    expecting = expecting + 2;
                    flag = 1;
                }
                
                else
				{
                    writeError("Protocol Violation Detected!");
                    connected = false; // Connection guard break
                    
					bzero(buf, sizeof(buf));
                    buf[0] = 5 + '0';
                    buf[1] = '0';
                    
					strlcpy(msg,"Protocol Violation\n", sizeof(msg));
                    int msgLength = strlen(msg);
                    
					char sizeOne = (msgLength / 10) + '0';
                    char sizeTwo = (msgLength % 10) + '0';
                    buf[2] = sizeOne;	// Payload Size byte Index 2
                    buf[3] = sizeTwo;	// Payload Size byte Index 3
                    
					strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    
                    exit(1);
                }
            }
            
            else if(expecting == 3)
			{
                if (buf[0] == '3')
				{
					bzero(buf, sizeof(buf));
	
    				buf[0] = 4 + '0';
    				buf[1] = '0';
    				
					number = arc4random_uniform(20);	// Generate random integer
					
					char* msg = switchCase(number); // Switch Statement Call
					int msgLength = strlen(msg);
				
                    char sizeOne = (msgLength / 10) + '0';
                    char sizeTwo = (msgLength % 10) + '0';
                  	buf[2] = sizeOne;	// Payload Size byte Index 2
                   	buf[3] = sizeTwo;	// Payload Size byte Index 3
                   	
                    strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    
                    expecting = expecting + 1;
                    connected = false;	// Connection guard break
                    disconnect = true;
                }
                
                else 
				{
                    writeError("Switch"); // Protcol Violation
                    connected = false;
                    
                    bzero(buf, sizeof(buf));
                    buf[0] = 5 + '0';
                    buf[1] = '0';
                    
                    char* msg = "Protocol Violation\n";
                    int msgLength = strlen(msg);
                    
                    char sizeOne = (msgLength / 10) + '0';
                    char sizeTwo = (msgLength % 10) + '0';
                    buf[2] = sizeOne;	// Payload Size byte Index 2
                    buf[3] = sizeTwo;	// Payload Size byte Index 3
                    
                    strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    
                    exit(1);
                }
                
            }
            
        }
        
        if(disconnect == true)
        {
        	writeError("Disconnecting"); // One run is complete and server 
        	close (s);					// closes the socket and exits
        	exit(1);
		}
        
    }
    
    return 0;
    
}
//-----------------------------------------------------------------------------
// Error Output Function:
void writeError(const char* error)
{

	fputs(error, stdout);

}
//-----------------------------------------------------------------------------
// Switch Function: 
// This function handles the 20 possible outputs from the server to the 
// client based on the input of a random integer.  
char* switchCase(int number)
{ 
	
	char* output;
	
	switch(number) 
	{	
		case 0  :
    	output = "It is certain\n\0";
        break;
        
		case 1  :
        output = "It is decidedly so\n\0";
        break;
        
		case 2  :
        output = "Without a doubt\n\0";
        break;
                        
		case 3  :
        output = "Yes, definitely\n\0";
        break;
                        
		case 4  :
        output = "You may rely on it\n\0";
        break;
                        
		case 5  :
        output = "As I see it, yes\n\0";
        break;
                            
        case 6  :
        output = "Most likely\n\0";
        break;
                            
        case 7  :
        output = "Outlook good\n\0";
        break;
                        
		case 8  :
        output = "Yes\n\0";
        break;
                            
        case 9  :
        output = "Signs point to yes\n\0";
        break;
    
		case 10  :
        output = "Reply hazy try again\n\0";
        break;
                        
		case 11  :
        output = "Ask again later\n\0";
        break;
                            
        case 12  :
        output = "Better not tell you now\n\0";
        break;
                            
        case 13  :
        output = "Cannot predict now\n\0";
        break;
                            
        case 14  :
        output = "Concentrate and ask again\n\0";
        break;
                            
        case 15  :
        output = "Don't count on it\n\0";
        break;
                            
        case 16  :
        output = "My reply is no\n\0";
        break;
                            
        case 17  :
        output = "My sources say no\n\0";
        break;
                            
        case 18  :
        output = "Outlook not so good\n\0";
        break;
                            
        case 19  :
        output = "Very doubtful\n\0";
        break;
    }
    
    return(output);
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
