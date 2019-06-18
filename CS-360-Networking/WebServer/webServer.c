//------------------------------------------------------------------------------
// Donald Lee Beadle
// CS 360
// Program #4 
// HTTP 0.9 Compatible Web Server:
// This program implements a GET request method and serves a file to the 
// calling browser. 
//------------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
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

#define SERVER_PORT 5421 // 8080 for cloud9
#define MAX_PENDING 5
#define MAX_LINE 2000000    // 2 MB buffer size
// ---------------------------------------------------------------------------
// Function Declarations: 
bool readRequest(char* buf);
bool isImageFile(char* path);
void numToASCII(int n, char* num);
void buildPath(char* buf, char* path);
void setContentType(char* mime);
void serveRootFile(char* path, int s);
void serveOtherFile(char* path, int s);
void serveError400(char* buf, int s);
void serveError404(char* buf, int s);
void serveError414(char* buf, int s);
void serveError501(char* buf, int s);
//-----------------------------------------------------------------------------
// Main Driver:
int main(int argc, char *argv[]) 
{
    
    signal(SIGINT, SIG_IGN);    // Signal to block control + c
	
    char buf[MAX_LINE];
    char path[1024];    // File directory storage set to 1024 bytes
    char* root;

    int s, new_s;
    int retval;
    int shutdown = 0;
    
    struct sockaddr_in sin;
    struct timeval tv;
    
    fd_set rfds;
    socklen_t new_len;
        
    if( argc == 2 ) // Command line argument
    {
        printf("Command Line Argument:  %s\n", argv[1]);
        root = argv[1];
    }
   
    else if( argc > 2 ) 
    {
        printf("More than one command line argument\n");
        printf("Program Exit...\n");
        exit(1);
    }
   
    else 
    {
        printf("Less than one command line argument\n");
        printf("Program Exit...\n");
        exit(1);
    } 
    
    // Address data structure
    bzero((char *) &sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
    
    // Passive Open
    if (( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
	    printf("%s \n:", "socket call failed");
        exit(1);
    }
    
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
	{
	    printf("%s \n:", "bind call failed");
        exit(1);
    }
    
    listen(s, MAX_PENDING);
    
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
            shutdown = 1;
        }
        
        FD_ZERO(&rfds);
        FD_SET(s, &rfds);
        
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        if( select(s + 1, &rfds, NULL, NULL, &tv) > 0 )
	    {
            if ( ( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
            {
                printf("%s \n:", "Accept Call Failed");
                exit(1);
            }
	    
	        bzero(buf, sizeof(buf));    // Clear Buffer
            bzero(path, sizeof(path));  // Zero Path 
	    
	        // If file URL is too long
	        if (recv(new_s, buf, sizeof(buf), 0) < 0)
	        {
                serveError414(buf, new_s);
            }
            
            else
            {
                // If request is NOT GET
                if (readRequest(buf) == false)
                {
	                bzero(buf, sizeof(buf));
                    serveError501(buf, new_s);    
	            }
	            
	            // If request is GET
                else
                {
                    buildPath(buf, path);
               
                    // If path is ROOT directory
                    if (strnlen(path) == 1) 
                    {
                        serveRootFile(root, new_s);
                    }
                    
                    // If path is NOT the ROOT directory
                    else
                    {
                        serveOtherFile(path, new_s);
                    }
            }
        }
        
	    bzero(buf, sizeof(buf));    // Clear the buffer
	    
        }
    }
    
    close (s);  // Close the socket
	
    return 0;
    
}
//------------------------------------------------------------------------------
// Read Request Function:
// This function converts the first three characters of a request to uppercase
// and checks if those characters are GET. Returns true if the request is a 
// GET and false in all other cases. 
bool readRequest(char* buf)
{
    
    char first = toupper(buf[0]);
    char second = toupper(buf[1]);
    char third = toupper(buf[2]);
    
    if (first == 'G' && second == 'E' && third == 'T')
    {
        return true;
    }
    
    return false;
    
}
//------------------------------------------------------------------------------
// Is Image Function:
// Check file extension. Returns true if extension is .png and false in all
// other cases. 
bool isImageFile(char* path)
{
    
    char* extension = strrchr(path, '.');
    
    if ((strncmp(extension, "png", 5) == 0) || (strncmp(extension, "js", 4) == 0))
    {
        return true;
    }
    
    else
    {
        return false;
    }
    
}
//------------------------------------------------------------------------------
// Number to ASCII Function:
// Converts a number n to an equivalent ASCII character. 
void numToASCII(int n, char* num)
{
    
    char temp[7];
    int i = 0;
    
    bzero(temp, sizeof(temp));
    
    while ((n / 10) != 0)
    {
        temp[i] = (n % 10) + '0';
        i++;
        n = n / 10;
    }
    
    temp[i] = (n % 10) + '0';
    int j = 0;
    
    for (; i >= 0; i--)
    {
        num[j] = temp[i];
        j++;
    }
    
}
//------------------------------------------------------------------------------
// Build Path Function:
// Builds the file path.
void buildPath(char* buf, char* path)
{
    
    // If buf[5] = SPACE
    if (buf[5] == ' ')
    {
        path[0] = '/'; 
    }
    
    else
    {
        int i = 5;
        int j = 0;
        char nextChar = buf[i];
        
        // While nextChar is NOT = SPACE
        while (nextChar != ' ')
        {
            path[j] = nextChar;
            i++;
            j++;
            nextChar = buf[i];
        }
    }
    
}
//------------------------------------------------------------------------------
// Set Content Type Function:
// Reads the file extension and sets the MIME type for the header. 
void setContentType(char* mime)
{
    
    char* extension = strrchr(mime, '.');
    
    if (strncmp(extension, ".png", 5) == 0)
    {
        strncpy(mime, "image/png", 20);
    }
    
    else if(strncmp(extension, ".css", 5) == 0)
    {
        strncpy(mime, "text/css", 20);
    }
    
    else if(strncmp(extension, ".js", 5) == 0)
    {
        strncpy(mime, "application/js", 20);
    }
    
    else
    {
        strncpy(mime, "text/html", 20);
    }
    
}
//------------------------------------------------------------------------------
// Server Error 400 Function:
// Returned when the request is malformed and cannot be fulfilled.
void serveError400(char* buf, int s)
{
    
	FILE* fin;
	struct stat fileObject;
    char number[7];
    int fileSize = 0;
    
    bzero(number, sizeof(number));
    fin = fopen("400.html", "r");
    stat("400.html", &fileObject);
    fileSize = fileObject.st_size;
    numToASCII(fileSize, number);

    strncpy(buf, "HTTP/1.0 400 Bad Request\r\n", 26);
    strncat(buf, "Connection: close\r\n", 19);
    strncat(buf, "Content-Type: text/html\r\n", 25);
    strncat(buf, "Content-Length: ", 16);
    strncat(buf, number, strlen(number));
    strncat(buf, "\r\n", 2);
    strncat(buf, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
    
    send(s, buf, strlen(buf), 0);
    fread(buf, fileSize, 1, fin);
    send(s, buf, fileSize, 0);
    close(s);
    
}
//------------------------------------------------------------------------------
// Serve Error 404 Function:
// Returned when the requested file cannot be found. 
void serveError404(char* msg, int s)
{

    FILE* fin;
    struct stat fileObject;
    char number[7];
    int fileSize = 0;
    
    bzero(number, sizeof(number));
    bzero(msg, sizeof(msg));
    fin = fopen("404.html", "r");
    stat("404.html", &fileObject);
    fileSize = fileObject.st_size;
    numToASCII(fileSize, number);
    
    strncpy(msg, "HTTP/1.0 404 Not Found\r\n", 24);
    strncat(msg, "Connection: close\r\n", 19);
    strncat(msg, "Content-Type: text/html\r\n", 25);
    strncat(msg, "Content-Length: ", 16);
    strncat(msg, number, strlen(number));
    strncat(msg, "\r\n", 2);
    strncat(msg, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
    
    send(s, msg, strlen(msg), 0);
    fread(msg, fileSize, 1, fin);
    send(s, msg, fileSize, 0);
    close(s);
    
}
// -----------------------------------------------------------------------------
// Serve Error 414 Function:
// Returned when the request length exceeds the input buffer for requests.
void serveError414(char* buf, int s)
{
    
	FILE* fin;
	struct stat fileObject;
	char number[7];
	int fileSize = 0;
    
    bzero(number, sizeof(number));
    fin = fopen("414.html", "r");
    stat("414.html", &fileObject);
    fileSize = fileObject.st_size;
    numToASCII(fileSize, number);

    strncpy(buf, "HTTP/1.0 Request-URI Too Long\r\n", 31);
    strncat(buf, "Connection: close\r\n", 19);
    strncat(buf, "Content-Type: text/html\r\n", 25);
    strncat(buf, "Content-Length: ", 16);
    strncat(buf, number, strlen(number));
    strncat(buf, "\r\n", 2);
    strncat(buf, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
    
    send(s, buf, strlen(buf), 0);
    fread(buf, fileSize, 1, fin);
    send(s, buf, fileSize, 0);
    close(s);
    
}
//------------------------------------------------------------------------------
// Serve Error 501 Function:
// Returned for any type of request other than GET.
void serveError501(char* buf, int s)
{
    
    FILE* fin;
    struct stat fileObject;
    char number[7];
    int fileSize = 0;
    
    bzero(number, sizeof(number));
    fin = fopen("501.html", "r");
    stat("501.html", &fileObject);
    fileSize = fileObject.st_size;
    numToASCII(fileSize, number);

    strncpy(buf, "HTTP/1.0 501 Not Handled\r\n", 26);
    strncat(buf, "Connection: close\r\n", 19);
    strncat(buf, "Content-Type: text/html\r\n", 25);
    strncat(buf, "Content-Length: ", 16);
    strncat(buf, number, strlen(number));
    strncat(buf, "\r\n", 2);
    strncat(buf, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
    
    send(s, buf, strlen(buf), 0);
    fread(buf, fileSize, 1, fin);
    send(s, buf, fileSize, 0);
    close(s);
    
}
//------------------------------------------------------------------------------
// Serve Root File Function:
// This function serves the index.html file of the root directory. Root 
// directory is WebServer in this case.
void serveRootFile(char* path, int s)
{

    FILE* fin;
    struct stat fileObject;
    char msg[MAX_LINE];
    char header[113];
    char number[7];
    int fileSize = 0;
    
    bzero(header, sizeof(header));
    bzero(msg, sizeof(msg));
    bzero(number, sizeof(number));
    stat("index.html", &fileObject);
    fileSize = fileObject.st_size;
    numToASCII(fileSize, number);
		
    strncpy(header, "HTTP/1.0 200 OK\r\n", 17);
    strncat(header, "Connection: close\r\n", 19);
    strncat(header, "Content-Type: text/html\r\n", 25);
    strncat(header, "Content-Length: ", 16);
    strncat(header, number, strlen(number));
    strncat(header, "\r\n", 2);
    strncat(header, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
		
	send(s, header, strlen(header), 0);
	fin = fopen("index.html", "r");
    fread(msg, fileSize, 1, fin);

    send(s, msg, fileSize, 0);
    
}
//------------------------------------------------------------------------------
// Serve Other File Function:
// This function serves any other file (with supported extensions) that is NOT 
// index.html. If the file cannot be accessed, a 404 Error is sent. 
void serveOtherFile(char* path, int s)
{
    
    char msg[MAX_LINE];
    
    bzero(msg, sizeof(msg));
    
    if( access( path, F_OK ) != -1 ) // File is accessible
    {  
        FILE* fin;
        struct stat fileObject;
        char header[113];
        char number[7];
        char mimeType[1024];
        int fileSize = 0;
    
        bzero(header, sizeof(header));
        bzero(number, sizeof(number));
        stat(path, &fileObject);
        fileSize = fileObject.st_size;
        strncpy(mimeType, path, 1024);
        setContentType(mimeType);
        numToASCII(fileSize, number);
            
        strncpy(header, "HTTP/1.0 200 OK\r\n", 17);
        strncat(header, "Connection: close\r\n", 19);
        strncat(header, "Content-Type: ", 14);
        strncat(header, mimeType, strlen(mimeType));
        strncat(header, "\r\n", 2);
        strncat(header, "Content-Length: ", 16);
        strncat(header, number, strlen(number));
        strncat(header, "\r\n", 2);
        strncat(header, "Server: cs360httpd/0.1 (Unix)\r\n\r\n", 33);
            
        send(s, header, strlen(header), 0);
            
        if (isImageFile(path) == true)
        {
            fin = fopen(path, "rb");
        }
            
        else
        {
            fin = fopen(path, "r");
        }
            
        fread(msg, fileSize, 1, fin);
        send(s, msg, fileSize, 0);
    }

    else // If file does NOT exist
    {
        serveError404(msg, s);
    }
    
}
//------------------------------------------------------------------------------
