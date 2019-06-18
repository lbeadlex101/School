CC=/usr/bin/gcc
CFLAGS=-Wall -g --std=c99

server: webServer.c
	$(CC) -o server $(CFLAGS) webServer.c

clean:
	rm -rf *o *core server
