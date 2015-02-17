#include "Block.h"
#include "AI.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void score_summary(int **board) {
	printf("Agg. height: %li, bumps: %li\n Cleared: %li, holes: %li\n Total: %f\n",
			score_height(board), score_bumps(board), score_cleared(board), score_holes(board), score_total(board));
}

int main(void) {
	Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
	int **b = board_create();

	board_print(b);
	score_summary(b);

	b[BOARD_HEIGHT-1][BOARD_WIDTH-1] = TEAL;
	b[BOARD_HEIGHT-2][BOARD_WIDTH-2] = RED;
	block_drop(blocks[0], 0, b, 0);
	block_drop(blocks[0], 0, b, 2);
	block_drop(blocks[0], 0, b, 4);
	board_print(b);
	score_summary(b);
	block_drop(blocks[1], 1, b, 7);
	board_print(b);
	score_summary(b);
	block_drop(blocks[1], 0, b, 4);
	board_print(b);
	score_summary(b);

	return 0;
}
