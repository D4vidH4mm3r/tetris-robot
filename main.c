#include "Block.h"
#include "AI.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	srand(time(NULL));
	int **b = board_create();

	Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};

	for (int i=0; i<10; i++) {
		Block *next = blocks[rand() % 7];
		Move best = best_move(b, next);
		move_print(&best);
		block_drop(next, best.rot, b, best.col);
		board_print(b);
		sleep(1);
	}
	return 0;
}
