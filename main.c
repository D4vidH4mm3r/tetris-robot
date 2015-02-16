#include "Block.h"
#include "AI.h"

int main(void) {
	int **board_main = board_create();
	board_print(board_main);
	printf("%d %d %d\n", score_height(board_main),
			score_holes(board_main),
			score_cleared(board_main));
	block_drop(&block_O, 0, board_main, 0);
	block_drop(&block_O, 0, board_main, 2);
	block_drop(&block_O, 0, board_main, 4);
	Move best = best_move_rot(board_main, &block_O, 0);
	move_print(&best);
	board_print(board_main);
	printf("%d %d %d\n", score_height(board_main),
			score_holes(board_main),
			score_cleared(board_main));
	return 0;
}
