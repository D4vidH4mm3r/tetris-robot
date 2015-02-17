LDFLAGS=-L/usr/include -lX11 
CFLAGS=-std=c99 
CC=gcc

all: main

grab: grab.c
	$(CC) $(CFLAGS) grab.c -o grab $(LDFLAGS)
