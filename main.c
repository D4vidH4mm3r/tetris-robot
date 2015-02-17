#include "Block.h"
#include "AI.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	srand(time(NULL));
	int **b = board_create();
	int cleared = 0;

	Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
	Block *queue = malloc(2*sizeof(Block));
	queue[0] = *blocks[rand() % 7];

	for (int i=0; i<100; i++) {
		queue[1] = *blocks[rand() % 7];

		Move *best = move_best(b, queue);
		move_print(best);

		move_execute(best, b);
		board_print(b);
		printf("Dropped\n");
		sleep(1);

		cleared += board_collapse(b);
		board_print(b);
		printf("Cleared?\n");
		sleep(1);

		queue[0] = queue[1];
	}
	return 0;
}
