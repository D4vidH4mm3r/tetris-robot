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

long score_height(int **board);
long score_holes(int **board);
long score_cleared(int **board);
long score_bumps(int **board);
double score_total(int **board);

Move *move_best(int **board, Block *blocks);
MoveSet *move_all(Block *block);
Move *move_best_lookahead(int **board, Block *blocks);
void move_copy(Move *to, Move *from);

void move_execute(Move *move, int **board);
void move_print(Move *m);

void move_destroy(Move *move);
void moveset_destroy(MoveSet *moves);

#endif
