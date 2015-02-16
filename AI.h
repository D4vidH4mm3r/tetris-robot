#include <stdio.h>
#ifndef _ai_def
#define _ai_def

typedef struct Move_t {
	int value;
	int rot;
	int col;
} Move;

int score_height(int **board);
int score_holes(int **board);
int score_cleared(int **board);
int score_bumps(int **board); /* TODO */
int score_total(int **board);
Move best_move_rot(int **board, Block *block, int rot);
Move best_move(int **board, Block *block);
void move_print(Move *m);

int score_height(int **board) {
	/* should it be aggregate or max? now max +1 ish */
	int row = 0;
	while (row < BOARD_HEIGHT) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (board[row][col]) {
				return BOARD_HEIGHT-row;
			}
		}
		row++;
	}
	return 0;
}

int score_holes(int **board) {
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

int score_cleared(int **board) {
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

int score_total(int **board) {
	/* here, weighting is important; higher is better */
	return score_cleared(board)*10 - score_holes(board)*15 - score_height(board)*5;
}

Move best_move_rot(int **board, Block *block, int rot) {
	int **copy = board_create();
	Move best;
	best.value = -1000;
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
	best.value = -1000;
	for (int r=0; r<block->nr; r++) {
		Move best_here = best_move_rot(board, block, r);
		if (best_here.value > best.value) {
			best = best_here;
		}
	}
	return best;
}

void move_print(Move *m) {
	printf("Rotate %d times and drop col %d for %d value\n", m->rot, m->col, m->value);
}

#endif
