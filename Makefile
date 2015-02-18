LDFLAGS = -L/usr/include -lX11 -lXtst
CFLAGS = -std=c99 #-Ofast
OBJS = Block.o AI.o Board.o
CC=gcc

all: bin/ai_demo bin/play

bin/ai_demo: ai_demo.c $(OBJS) common.h
	$(CC) $(CFLAGS) $(OBJS) ai_demo.c -o bin/ai_demo

bin/play: play.c $(OBJS) common.h
	$(CC) $(CFLAGS) $(OBJS) play.c -o bin/play $(LDFLAGS)

clean:
	rm -f *.o
	rm -f bin/*
