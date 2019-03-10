CFLAGS = -std=c++17
#-Ofast -march=native -flto -fwhole-program
CC=g++

all: bin/ai_demo bin/play

bin/ai_demo: demo.cpp common.hpp Board.hpp AI.hpp
	$(CC) $(CFLAGS) $(OBJS) demo.cpp -o bin/ai_demo

bin/test: test.cpp common.hpp Board.hpp
	$(CC) $(CFLAGS) $(OBJS) test.cpp -o bin/test

bin/play: play.c Interaction.o common.hpp
	$(CC) $(CFLAGS) $(OBJS) Interaction.o play.c -o bin/play -lgdi32

bin/watch: watch.c Interaction.o common.hpp
	$(CC) $(CFLAGS) $(OBJS) Interaction.o watch.c -o bin/watch -lgdi32

Interaction.o: Interaction.h Interaction.c
	$(CC) $(CFLAGS) $(OBJS) -c Interaction.c $(LDFLAGS)

clean:
	rm -f *.o
	rm -f bin/*
