#include "Block.h"

int main(void) {
	int **board_main = board_create();
	board_print(board_main);
	block_addblock(&block_I, 0, board_main, 2, 2);
	board_print(board_main);
	return 0;
}
