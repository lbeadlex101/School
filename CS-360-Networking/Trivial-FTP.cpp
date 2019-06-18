//-----------------------------------------------------------------------------
//	Donald Lee Beadle
//	CS 360
//	(ROUGH) Trivial File Transfer Protocol:
// 	This program implements the server of a TFTP. 
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define SERVER_PORT 5421
#define MAX_PENDING 5
#define MAX_LINE 517 
//-----------------------------------------------------------------------------
// Structs:
struct RWgram
{
    short opcode;
    char filename[514];
};

struct dea_dgram
{
    short opcode;
    short block_num;
    char data[513];
};
//-----------------------------------------------------------------------------
// Function Declarations: 
void promsg(int socket, struct RWgram message, struct dea_dgram dea, int code);
void handler(int sig);
void writeError(const char* error);
//-----------------------------------------------------------------------------
// Global Variables: 
int timeExpired = 0;
int blockCount = 1;
int numCharacters = 0;
int lastCount = 0;
FILE* fin;
//-----------------------------------------------------------------------------
// Main Driver:
int main() 
{

	struct RWgram message;
    struct dea_dgram dea;
	struct timeval tv; 
	struct sockaddr_in sin;
	
	signal(SIGINT, SIG_IGN);
    signal(SIGALRM, handler);
    fd_set rfds;
   
    int s; 
    int retval = 0;
    int shutdown = 0;
    int code = 0;
    
    bzero((char *) &sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = INADDR_ANY; 
    sin.sin_port = htons(SERVER_PORT); 
    
    // Passive Open:
    if (( s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        fprintf(stdout, "Socket call failed \n");
        exit(1);
    }
    
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
    {
        fprintf(stdout, "Bind call failed \n");
        exit(1);
    }
    
    // While Server is not shutdown
    while (shutdown == 0)
	{
    	FD_ZERO(&rfds);
        FD_SET(0,&rfds);
        
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        retval = select(1, &rfds, NULL, NULL, &tv);

    	if(retval== 1)
		{
            shutdown = 1;
        }
        
        FD_ZERO(&rfds);
        FD_SET(s,&rfds);
        
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        if(select(s + 1, &rfds, NULL, NULL, &tv) > 0)
		{
            promsg(s, message, dea, code);
        }    
    }
    
    close (s);
    
    return 0;
    
}
//-----------------------------------------------------------------------------
// Process Message Function:
void promsg(int socket, struct RWgram message, struct dea_dgram dea, int code)
{

	//if(timeExpired == 1)
	//{
	//	resend(dea, code);
	//}

    struct sockaddr sin; 
    socklen_t new_len= sizeof(sin); 
    int i = 0;
	int c;
	int transmissionComplete = 0;
    int lengthLast = 0;
	char tempBuf[513];
	
    bzero(&message, sizeof(message));	// Zero message
    bzero(&dea, sizeof(dea));	// Zero dea
    bzero(tempBuf, sizeof(tempBuf));
    
	recvfrom(socket, &message, sizeof(message), 0, &sin, &new_len);
    code = 0;
	 
    switch (ntohs(message.opcode))
    {
        case 1: 
	    	fin = fopen(message.filename, "r"); // Open file.
	    	
            if (!fin)
			{
                dea.opcode = htons(5); // Host to Network
                dea.block_num = htons(1); // Host to Network
                strncat(dea.data, "File not found!", sizeof(dea.data) - 1);
                transmissionComplete = 1;
        	}
                
            else
			{
                while ((c = fgetc(fin)) != EOF && i < 512) 
				{
                    tempBuf[i] = c;
                    i = i + 1;
                    lastCount = i;
                }
                
                tempBuf[i] = '\0';
        		dea.opcode = htons(3);
        		dea.block_num = htons(blockCount);
        		blockCount = blockCount + 1;
        		strncpy(dea.data, tempBuf, sizeof(dea.data));
            }
            code = 2;
            break;
            
        case 2: // WRQ
            dea.opcode = htons(5);
            dea.block_num = 0;
            strncat(dea.data, "Write request not supported!", sizeof(dea.data) - 1);
            code = 2;
            break;
            
        case 3: // DAT
            dea.opcode = htons(5);
            dea.block_num = 0;
            strncat(dea.data, "Not supported by server", sizeof(dea.data) - 1);
            code = 3;
            break;
            
        case 4: // ACK
            alarm(0);
            if (transmissionComplete == 0)
			{
                bzero(&dea, sizeof(dea));
                bzero(tempBuf, sizeof(tempBuf));
                
                while ((c = fgetc(fin)) != EOF && i < 512) 
				{             
                    tempBuf[i] = c;
                    i = i + 1;
                    lastCount = i;      
                }
                
                tempBuf[i] = '\0'; // Assign Null Byte
                
                if (lastCount < 512)	// Data packet < 512
				{
                    char tempHold[lastCount];	
                    bzero(tempHold, sizeof(tempHold));
                    i = 0;
                    
                    while (i < lastCount)
					{
                        tempHold[i] = tempBuf[i];
                        i = i + 1;
                    }
                    
                    lengthLast = strlen(tempHold);
                    dea.opcode = htons(3); // Host to network
        		    dea.block_num = htons(blockCount); // Host to network
        		    blockCount = blockCount + 1;
        		    strncat(dea.data, tempHold, sizeof(dea.data));
                    transmissionComplete = 1;
                    code = 6;
                }
                
                else
				{
                    dea.opcode = htons(3);	// Host to network
        		    dea.block_num = htons(blockCount);	// Host to network
        		    blockCount = blockCount + 1;
        		    strncat(dea.data, tempBuf, sizeof(dea.data));
                    code = 4; 
                }
        		
			    if (lastCount < 512)
				{
                    blockCount = 1;
                    fclose(fin);
                }	 
                
            }
            
            else
			{
                dea.opcode = htons(4);	// Host to network
        		dea.block_num = htons(1);	// Host to network
                code = 7;
            }
            break;
    }
    
    if(code == 2 || code == 3 || code == 4 || code == 5)
    {
        sendto(socket, &dea, sizeof(dea), 0, &sin, new_len);
        alarm(3); 
    } 
    
    if(code == 6)
    {
        sendto(socket, &dea, lengthLast + 4, 0, &sin, new_len);
        alarm(3); 
    } 
    
    if(code == 7)
    {
        sendto(socket, &dea, sizeof(dea), 0, &sin, new_len);
        alarm(3); 
    } 
    
    lastCount = 0;
    numCharacters = 0;

}
//-----------------------------------------------------------------------------
// Handler Function:
// Housekeeping.
void handler(int sig) 
{

	int save_errno = errno;
	
	timeExpired = 1; 
	
	errno = save_errno;
	
}
//-----------------------------------------------------------------------------
// Write Error Function: 
// Used to print strings and for debugging purposes. 
void writeError(const char* error)
{

    fputs(error, stdout);
    
}
//-----------------------------------------------------------------------------


