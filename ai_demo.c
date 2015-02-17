#include "Block.h"
#include "AI.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int random_blockno() {
	return rand() % 7;
}

int main(void) {
	srand(time(NULL));
	int **b = board_create();
	int cleared = 0;

	Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
	Block *queue = malloc(2*sizeof(Block));
	queue[0] = *blocks[random_blockno()];

	while (1) {
		queue[1] = *blocks[random_blockno()];

		Move *best = move_best_lookahead(b, queue);
		//move_print(best);
		move_execute(best, b);

		move_destroy(best);

		if (board_dead(b)) {
			board_print(b);
			printf("Dead :(\n");
			break;
		}
		cleared += board_collapse(b);
		//board_print(b);
		printf("%d cleared\n", cleared);

		queue[0] = queue[1];
	}
	return 0;
}
