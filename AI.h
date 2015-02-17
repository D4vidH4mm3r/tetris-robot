#include <stdio.h>
#include <float.h>
#include "common.h"
#include "Block.h"
#ifndef _ai_def
#define _ai_def

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
void move_execute(Move *move, int **board);
void move_print(Move *m);
MoveSet *move_all(Block *block);

long score_height(int **board) {
	int block_seen[BOARD_WIDTH];
	for (int i=0; i<BOARD_WIDTH; i++) {
		block_seen[i] = BOARD_HEIGHT;
	}
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if ((row < block_seen[col]) && board[row][col]) {
				block_seen[col] = row;
			}
		}
	}
	long height = 0;
	for (int col=0; col<BOARD_WIDTH; col++) {
		height += (BOARD_HEIGHT-block_seen[col]);
	}
	return height;
}

long score_holes(int **board) {
	int has_been_block[BOARD_WIDTH] = {0};
	long holes = 0;
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (board[row][col]) {
				has_been_block[col] = 1;
			} else if (has_been_block[col]) {
				holes++;
			}
		}
	}
	return holes;
}

long score_cleared(int **board) {
	long cleared = 0;
	for (int row=0; row<BOARD_HEIGHT; row++) {
		int clears = 1;
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (!board[row][col]) {
				clears = 0;
			}
		}
		if (clears) {
			cleared++;
		}
	}
	return cleared;
}

long score_bumps(int **board) {
	int block_seen[BOARD_WIDTH];
	for (int i=0; i<BOARD_WIDTH; i++) {
		block_seen[i] = BOARD_HEIGHT;
	}
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if ((row < block_seen[col]) && board[row][col]) {
				block_seen[col] = row;
			}
		}
	}
	long bumps = 0;
	for (int col=0; col<BOARD_WIDTH-1; col++) {
		bumps += abs(block_seen[col] - block_seen[col+1]);
	}
	return bumps;
}

/* values from https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/ */
double score_total(int **board) {
	/* here, weighting is important; higher is better */
	return score_cleared(board)*0.99275
		+ score_holes(board)*(-0.46544)
		+ score_height(board)*(-0.66569)
		+ score_bumps(board)*(-0.24077);
}

void move_execute(Move *move, int **board) {
	block_drop(move->block, move->rot, board, move->col);
}

Move *move_best(int **board, Block *block) {
	int **copy = board_create();
	Move *best = NEW(Move);;
	best->value = -DBL_MAX;
	best->block = block;
	for (int rot=0; rot<block->nr; rot++) {
		for (int col=0; col<BOARD_WIDTH-block->w[rot]+1; col++) {
			board_copy(copy, board);
			block_drop(block, rot, copy, col);
			double score = score_total(copy);
			if (score > best->value) {
				best->value = score;
				best->col = col;
				best->rot = rot;
			}
		}
	}
	printf("Move_best returning\n");
	return best;
}

MoveSet *move_all(Block *block) {
	MoveSet *ms = NEW(MoveSet);
	int length = 0;
	for (int rot=0; rot<block->nr; rot++) {
		int trycols = BOARD_WIDTH-block->w[rot]+1;
		length += trycols;
	}
	ms->length = length;
	ms->moves = malloc(length*sizeof(Move));
	ms->block = block;
	return ms;
}

void move_print(Move *m) {
	printf("Rotate %d times and drop col %d for %f value\n", m->rot, m->col, m->value);
}

#endif
