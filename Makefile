LDFLAGS = -L/usr/include -lX11
CFLAGS = -std=c99
OBJS = Block.o AI.o Board.o
CC=gcc

all: main

main: main.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main.c -o main

grab: grab.c Board.o
	$(CC) $(CFLAGS) Board.o grab.c -o grab $(LDFLAGS)

clean:
	rm -f *.o
	rm -f grab
	rm -f main
