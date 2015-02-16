#include <stdio.h>
#include <float.h>
#ifndef _ai_def
#define _ai_def

typedef struct Move_t {
	double value;
	int rot;
	int col;
} Move;

double score_height(int **board);
double score_holes(int **board);
double score_cleared(int **board);
double score_bumps(int **board);
double score_total(int **board);
Move best_move_rot(int **board, Block *block, int rot);
Move best_move(int **board, Block *block);
void move_print(Move *m);

double score_height(int **board) {
	int block_seen[BOARD_WIDTH] = {0};
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (!block_seen[col] && board[row][col]) {
				block_seen[col] = row;
			}
		}
	}
	int height = 0;
	for (int col=0; col<BOARD_WIDTH-1; col++) {
		height += (BOARD_HEIGHT-block_seen[col]);
	}
	return height;
}

double score_holes(int **board) {
	int has_been_block[BOARD_WIDTH] = {0};
	int holes = 0;
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

double score_cleared(int **board) {
	int cleared = 0;
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

double score_bumps(int **board) {
	int block_seen[BOARD_WIDTH] = {0};
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (!block_seen[col] && board[row][col]) {
				block_seen[col] = row;
			}
		}
	}
	int bumps = 0;
	for (int col=0; col<BOARD_WIDTH-1; col++) {
		bumps += abs(block_seen[col] - block_seen[col+1]);
	}
	return bumps;
}

/* values from https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/ */
double score_total(int **board) {
	/* here, weighting is important; higher is better */
	return score_cleared(board)*0.99275
		- score_holes(board)*0.46544
		- score_height(board)*0.66569
		- score_bumps(board)*0.24077;
}

Move best_move_rot(int **board, Block *block, int rot) {
	int **copy = board_create();
	Move best;
	best.value = -DBL_MAX;
	for (int col=0; col<BOARD_WIDTH-block->w[rot]; col++) {
		board_copy(copy, board);
		block_drop(block, rot, copy, col);
		int score = score_total(copy);
		if (score > best.value) {
			best.value = score;
			best.col = col;
			best.rot = rot;
		}
	}
	return best;
	//board_destroy(copy);
}

Move best_move(int **board, Block *block) {
	Move best;
	best.value = -DBL_MAX;
	for (int r=0; r<block->nr; r++) {
		Move best_here = best_move_rot(board, block, r);
		if (best_here.value > best.value) {
			best = best_here;
		}
	}
	return best;
}

void move_print(Move *m) {
	printf("Rotate %d times and drop col %d for %f value\n", m->rot, m->col, m->value);
}

#endif
