LDFLAGS=-lncurses
CFLAGS=-std=c99

all: main

grab: grab.c
	gcc grab.c -L/usr/include -lX11 -o grab
