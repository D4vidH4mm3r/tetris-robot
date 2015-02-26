#include "Block.h"
#include "AI.h"
#include <sys/time.h>
#include <stdlib.h>

#define STACKING 0

int random_blockno() {
	return rand() % 7;
}

int main(void) {
	struct timespec ts;
	ts.tv_sec=0;
	ts.tv_nsec=100000000L;

	srand(time(NULL));
	Board b = board_create();
	int cleared = 0;

	Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
	Block *queue = malloc(2*sizeof(Block));
	queue[0] = *blocks[random_blockno()];

#if STACKING
	ai_build_up = 1;
#endif

	for (int i=0; i<2000; i++) {
		queue[1] = *blocks[random_blockno()];

		Move *best = move_best_lookahead(b, &queue[0], &queue[1]);
		move_execute(best, b);
		move_destroy(best);
		board_print(b);

#if STACKING
		if (score_height(b) > 85) {
			printf("Switching to destroy\n");
			ai_build_up = 0;
		} else if (score_height(b) < 20) {
			printf("Switching to build\n");
			ai_build_up = 1;
		}
#endif

		if (board_dead(b)) {
			board_print(b);
			printf("%d cleared\n", cleared);
			printf("Dead :(\n");
			board_destroy(b);
			b = board_create();
		}
		cleared += board_collapse(b);

		queue[0] = queue[1];
		nanosleep(&ts);
	}

	board_print(b);
	printf("%d cleared\n", cleared);
	board_destroy(b);
	free(queue);
	return 0;
}
