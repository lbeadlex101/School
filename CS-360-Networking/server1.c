//-----------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #2
// Magic 8 Ball Server:
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
bool isSane(const char* buffer);
//-----------------------------------------------------------------------------
// Main Driver:
int main() 
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    socklen_t new_len;
    int s, new_s;
    
    // ADS
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
    
    // In Waiting for CLient Frame
    while (1)
	{
    	if (( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
		{
            writeError("accept call failed");
            exit(1);
        }
        
        int expecting = 1;
        int receiving = 1;
        int flag = 0;
        char msg[32];
       
	    bzero(msg, sizeof(msg));
       
        while (receiving == 1)
		{
            bzero(buf,sizeof(buf));
            recv(new_s,buf,sizeof(buf),0);
            
            if (isSane(buf) == false)
			{
            	writeError("Protocol Violation Detected!");
                receiving = 0;
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
                    char first = (msgLength / 10) + '0';
                    char second = (msgLength % 10) + '0';
                    buf[2] = first;
                    buf[3] = second;
                    strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    expecting = expecting + 2;
                    flag = 1;
                }
                
                else
				{
                    writeError("Protocol Violation Detected!");
                    receiving = 0;
                    bzero(buf, sizeof(buf));
                    buf[0] = 5 + '0';
                    buf[1] = '0';
                    strlcpy(msg,"Protocol Violation\n", sizeof(msg));
                    int msgLength = strlen(msg);
                    char first = (msgLength / 10) + '0';
                    char second = (msgLength % 10) + '0';
                    buf[2] = first;
                    buf[3] = second;
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
                    int randNum = arc4random_uniform(20);
                    randNum = randNum % 20;
                    writeError("hello3");
                    switch(randNum) 
					{
                        case 0  :
                            strlcpy(msg, "It is certain\n\0", sizeof(msg)-1);
                            break;
                        case 1  :
                            strlcpy(msg, "It is decidedly so\n\0", sizeof(msg) - 1);
                            break;
                        case 2  :
                            strlcpy(msg,"Without a doubt\n\0", sizeof(msg) - 1);
                            break;
                        case 3  :
                            strlcpy(msg, "Yes, definitely\n\0", sizeof(msg)- 1);
                            break;
                        case 4  :
                            strlcpy(msg, "You may rely on it\n\0", sizeof(msg) - 1);
                            break;
                        case 5  :
                            strlcpy(msg, "As I see it, yes\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 6  :
                            strlcpy(msg, "Most likely\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 7  :
                            strlcpy(msg, "Outlook good\n\0", sizeof(msg) - 1);
                            break;
                        case 8  :
                            strlcpy(msg, "Yes\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 9  :
                            strlcpy(msg, "Signs point to yes\n\0", sizeof(msg) - 1);
                            break;
                        case 10  :
                            strlcpy(msg, "Reply hazy try again\n\0", sizeof(msg) - 1);
                            break;
                        case 11  :
                            strlcpy(msg, "Ask again later\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 12  :
                            strlcpy(msg, "Better not tell you now\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 13  :
                            strlcpy(msg, "Cannot predict now\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 14  :
                            strlcpy(msg, "Concentrate and ask again\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 15  :
                            strlcpy(msg, "Don't count on it\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 16  :
                            strlcpy(msg, "My reply is no\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 17  :
                            strlcpy(msg, "My sources say no\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 18  :
                            strlcpy(msg, "Outlook not so good\n\0", sizeof(msg) - 1);
                            break;
                            
                        case 19  :
                            strlcpy(msg, "Very doubtful\n\0", sizeof(msg) - 1);
                            break;
                    }
                    
                    int msgLength = strlen(msg);
                    char first = (msgLength / 10) + '0';
                    char second = (msgLength % 10) + '0';
                    buf[2] = first;
                    buf[3] = second;
                    strlcat(buf, msg, sizeof(buf));
                    send(new_s, buf, sizeof(buf), 0);
                    expecting = expecting + 1;
                    receiving = 0;
                }
                
                else 
				{
                    writeError("Protocol Violation Detected! Closing..");
                    receiving = 0;
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
                    send(new_s, buf, sizeof(buf), 0);
                    exit(1);
                }
                
            }
            
        }
        
        close (new_s);
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
// Sanity Check: 
bool isSane(const char* buffer)
{

	int firstSize = buffer[2] - '0';
	int secondSize = buffer[3] - '0';
	int size = (firstSize * 10) + secondSize;
	return (size + 4) == strlen(buffer);

}
//-----------------------------------------------------------------------------
