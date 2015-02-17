#include "AI.h"

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
	//board_destroy(copy);
	return best;
}

MoveSet *move_all(Block *block) {
	/* NOTE: angiver ikke korrekt value */
	MoveSet *ms = NEW(MoveSet);
	int length = 0;

	for (int rot=0; rot<block->nr; rot++) {
		int trycols = BOARD_WIDTH-block->w[rot]+1;
		length += trycols;
	}

	ms->length = length;
	ms->moves = malloc(length*sizeof(Move));
	ms->block = block;

	int moveno = 0;
	for (int rot=0; rot<block->nr; rot++) {
		int trycols = BOARD_WIDTH-block->w[rot]+1;
		for (int col=0; col<trycols; col++) {
			Move *current = &ms->moves[moveno];
			current->col = col;
			current->rot = rot;
			current->block = block;
			current->value = 0;
			moveno++;
		}
	}
	return ms;
}

Move *move_best_lookahead(int **board, Block *blocks) {
	MoveSet *first_moves = move_all(&blocks[0]); // all moves with first block
	Move *best = NEW(Move); // best move with second block
	best->value = -DBL_MAX;
	best->block = &blocks[1];

	int **copy = board_create();

	for (int i=0; i<first_moves->length; i++) {
		board_copy(copy, board);
		Move *current = &first_moves->moves[i];
		move_execute(current, copy);
		Move *best_next = move_best(copy, best->block);
		if (best_next->value > best->value) {
			move_copy(best, best_next);
			best->prev = current;
		}
	}

	move_copy(best, best->prev);
	moveset_destroy(first_moves);
	//board_destroy(copy);
	return best;
}

void move_copy(Move *to, Move *from) {
	to->block = from->block;
	to->value = from->value;
	to->rot   = from->rot;
	to->col   = from->col;
	to->prev  = from->prev;
}

void move_print(Move *m) {
	printf("Rotate %d times and drop col %d for %f value\n", m->rot, m->col, m->value);
}

void move_destroy(Move *move) {
	free(move);
}

void moveset_destroy(MoveSet *moves) {
	free(moves);
}
