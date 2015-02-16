#include "Block.h"

int main(void) {
	int **board_main = board_create();
	board_print(board_main);
	block_drop(&block_I, 1, board_main, 0);
	block_drop(&block_O, 0, board_main, 0);
	board_print(board_main);
	return 0;
}
