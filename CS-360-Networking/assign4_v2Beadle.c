//-----------------------------------------------------------------------------
//	Donald Lee Beadle
//	CS 360
//	(ROUGH) Trivial File Transfer Protocol:
// 	This program implements the server of a TFTP. 
//  Note: This version prints several debugging statements to the server 
//  console. Alarms are also not implemented. 
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
void runProtocol(int socket, struct RWgram message, struct dea_dgram dea);
void handler(int sig);
// void resend();
//-----------------------------------------------------------------------------
// Global Variables: 
int timeExpired = 0;	// Maintain state of alarms
int blockCount = 1;		// Tracks number of blocks
FILE* fin;				// File ptr f in 
//-----------------------------------------------------------------------------
// Main Driver:
int main() 
{

	struct RWgram message;
    struct dea_dgram dea;
    struct timeval tv;
    struct sockaddr_in sin; 

 	fd_set rfds;
 	
    int s; 
    int retval;
    int shutdown = 0;
    
    bzero((char *) &sin, sizeof(sin)); 
    sin.sin_family = AF_INET; 
    sin.sin_addr.s_addr = INADDR_ANY; 
    sin.sin_port = htons(SERVER_PORT); 
    
    // Open
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
    
    // While server is NOT shutdown
    while (shutdown == 0) 
	{
        FD_ZERO(&rfds);
        FD_SET(0,&rfds);
        
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        retval = select(1, &rfds, NULL, NULL, &tv);
        
        if(retval == -1)
		{
            printf("%s \n:", "Select Error");
        }

    	if(retval == 1)
		{
			printf("%s \n:", "retval = 1");
            shutdown = 1;
        }
        
        FD_ZERO(&rfds);
        FD_SET(s,&rfds);
        
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        if( select(s + 1, &rfds, NULL, NULL, &tv) > 0 )
		{
            runProtocol(s, message, dea);
            printf("%s \n", "-----------------------------------------------");
        }    
    }
    
    close (s);
    
    return 0;
    
}
//-----------------------------------------------------------------------------
// Run Protocol Function: 
// This function accepts a socket, read/write gram, and data gram to process 
// and send messages. Message handling is based off the opcode of the 
// struct message.  
void runProtocol(int socket, struct RWgram message, struct dea_dgram dea)
{

	//if(timeExpired == 1)
	//{
	//	resend(dea, code);
	//}

    struct sockaddr sin; 
    socklen_t new_len= sizeof(sin);
	 
	int code = 0; 
    int i = 0;
	int c;
    int lengthLast = 0;
    int prevIndex = 0;
	int transmissionComplete = 0;
	
	char tempBuf[513];
	
    bzero(&message, sizeof(message));	// Zero message
    bzero(&dea, sizeof(dea));	// Zero dea
    bzero(tempBuf, sizeof(tempBuf));
    
	recvfrom(socket, &message, sizeof(message), 0, &sin, &new_len);
    code = 0;
    
    switch (ntohs(message.opcode))
    {
        case 1: // RRQ
        printf("%s \n","Case 1: RRQ");
	    	fin = fopen(message.filename, "r"); // Open file.
            if (fin == NULL)
			{
				printf("%s \n", "CASE 1 RRQ : fin == NULL");
                dea.opcode = htons(5); // Host to Network
                dea.block_num = htons(1); // Host to Network
                strncat(dea.data, "File not found!", sizeof(dea.data) - 1);
                transmissionComplete = 1;
                code = 2;
        	}
                
            else
			{
				printf("%s \n", "CASE 1 RRQ : fin != NULL");
                while ((c = fgetc(fin)) != EOF && i < 512) 
				{
                    tempBuf[i] = c;
                    i = i + 1;
                    prevIndex = i;
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
        printf("%s \n","Case 2: WRQ");
            dea.opcode = htons(5);
            dea.block_num = 0;
            strncat(dea.data, "Write request not supported!", sizeof(dea.data) - 1);
            code = 2;
            break;
            
        case 3: // DAT
        	printf("%s \n","Case 3: DAT");
            dea.opcode = htons(5);
            dea.block_num = 0;
            strncat(dea.data, "Not supported by server", sizeof(dea.data) - 1);
            code = 3;
            break;
            
        case 4: // ACK
            //alarm(0);
            printf("%s \n","Case 4: ACK");
            if (transmissionComplete == 0 && fin != NULL)
			{
				printf("%s \n", "CASE 4 ACK : (transmissionComplete == 0 && fin != NULL)");
                bzero(&dea, sizeof(dea));
                bzero(tempBuf, sizeof(tempBuf));
                
                while ((c = fgetc(fin)) != EOF && i < 512) 
				{             
                    tempBuf[i] = c;
                    i = i + 1;
                    prevIndex = i;      
                }
                
                tempBuf[i] = '\0'; // Assign Null Byte
                
                if (prevIndex < 512)	// Data packet < 512 // Trace instances
				{
					printf("%s \n","CASE 4 ACK : (prevIndex < 512)");
                    char tempHold[prevIndex];	
                    bzero(tempHold, sizeof(tempHold));
                    i = 0;
                    
                    while (i < prevIndex)
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
					printf("%s \n","CASE 4 ACK : (prevIndex !< 512)");
                    dea.opcode = htons(3);	// Host to network
        		    dea.block_num = htons(blockCount);	// Host to network
        		    blockCount = blockCount + 1;
        		    strncat(dea.data, tempBuf, sizeof(dea.data));
                    code = 4; 
                }
        		
			    if (prevIndex < 512) // Potential logic error
				{
					printf("%s \n","CASE 4 ACK : (prevIndex < 512)");
                    blockCount = 1;
                    fclose(fin);
                }	 
                
            }
            
            else
			{
				printf("%s \n", "CASE 4 ACK : (transmissionComplete != 0 || fin == NULL)");
                dea.opcode = htons(4);	// Host to network
        		dea.block_num = htons(1);	// Host to network
                code = 7;
            }
            break;
    }
    
    if(code == 2 || code == 3 || code == 4 || code == 5)
    {
		printf("%s \n", "code == 2 || code == 3 || code == 4 || code == 5");
        sendto(socket, &dea, sizeof(dea), 0, &sin, new_len);
        //alarm(3); 
    } 
    
    if(code == 6)
    {
    	printf("%s \n", "code == 6");
        sendto(socket, &dea, lengthLast + 4, 0, &sin, new_len);
        //alarm(3); 
    } 
    
    if(code == 7)
    {
    	printf("%s \n", "code == 7");
        sendto(socket, &dea, sizeof(dea), 0, &sin, new_len);
        //alarm(3); 
    } 
    
    prevIndex = 0;

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
// void resend()
// {
//
// }
//-----------------------------------------------------------------------------



