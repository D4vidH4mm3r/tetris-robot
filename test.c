#include "Block.h"
#include "AI.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void score_summary(int **board) {
	printf("Agg. height: %li, bumps: %li\n Cleared: %li, holes: %li\n", 
			score_height(board), score_bumps(board), score_cleared(board), score_holes(board));
}

int main(void) {
	//Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
	int **b = board_create();

	board_print(b);
	score_summary(b);

	b[BOARD_HEIGHT-1][BOARD_WIDTH-1] = TEAL;
	board_print(b);
	score_summary(b);

	return 0;
}
