CFLAGS = -std=c99 -Ofast -march=native -flto -fwhole-program
OBJS = Block.o AI.o Board.o
CC=gcc

all: bin/ai_demo bin/play

bin/ai_demo: ai_demo.c $(OBJS) common.h
	$(CC) $(CFLAGS) $(OBJS) ai_demo.c -o bin/ai_demo -L/usr/include

bin/play: play.c $(OBJS) Interaction.o common.h
	$(CC) $(CFLAGS) $(OBJS) Interaction.o play.c -o bin/play -lgdi32

Interaction.o: Interaction.h Interaction.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -c Interaction.c $(LDFLAGS)

clean:
	rm -f *.o
	rm -f bin/*
