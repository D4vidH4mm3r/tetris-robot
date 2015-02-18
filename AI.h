#ifndef _ai_def
#define _ai_def

#include <stdio.h>
#include <float.h>
#include "common.h"
#include "Block.h"

typedef struct Move_t {
	Block *block;
	double value;
	int rot;
	int col;
	struct Move_t *prev;
} Move;

typedef struct MoveSet_t {
	Block *block;
	int length;
	Move *moves;
} MoveSet;

long score_height(Board board);
long score_holes(Board board);
long score_cleared(Board board);
long score_bumps(Board board);
double score_total(Board board);

Move *move_best(Board board, Block *blocks);
MoveSet *move_all(Block *block);
Move *move_best_lookahead(Board board, Block *current, Block *next);
void move_copy(Move *to, Move *from);

void move_execute(Move *move, Board board);
void move_print(Move *m);

void move_destroy(Move *move);
void moveset_destroy(MoveSet *moves);

#endif
