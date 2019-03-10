CFLAGS = -std=c++17
#-Ofast -march=native -flto -fwhole-program
CC = g++
HEADERS = common.hpp Board.hpp Block.hpp

all: bin/ai_demo bin/play

bin/ai_demo: demo.cpp AI.hpp $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) demo.cpp -o bin/ai_demo

bin/test: test.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) test.cpp -o bin/test

bin/play: play.c Interaction.o $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) Interaction.o play.c -o bin/play -lgdi32

bin/watch: watch.c Interaction.o $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) Interaction.o watch.c -o bin/watch -lgdi32

Interaction.o: Interaction.h Interaction.c AI.hpp $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -c Interaction.c $(LDFLAGS)

clean:
	rm -f *.o
	rm -f bin/*
