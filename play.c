#include "Interaction.h"

int main(int argc, char const *argv[]) {

	Corners curr_block = {218, 1792, 237, 1776};
	Corners next_block = {260, 1975, 264, 1971};
	//Corners curr_block = {103, 852, 112, 834};
	//Corners next_block = {134, 1000, 142, 990};

	Board board = board_create();

	Display *display = XOpenDisplay(NULL);

	Block *blocks[8] = {NULL, &block_Lr, &block_Zr, &block_O, &block_L, &block_I, &block_T, &block_Z};
	Block *queue[2] = {0, 0};

	Color first = 0;
	Color next;
	while (!first) {
		first = guess_color_area(curr_block, display);
	}
	queue[0] = blocks[first];

	while (1) {
		next = guess_color_area(next_block, display);
		queue[1] = blocks[next];

		printf("Current:\n");
		color_print(queue[0]->c);

		printf("Next:\n");
		color_print(queue[1]->c);
		printf("---------\n");

		Move *best = move_best_lookahead(board, queue[0], queue[1]);
		move_print(best);
		move_execute(best, board);
		move_send(best, display);
		move_destroy(best);
		board_collapse(board);
		board_print(board);

		queue[0] = queue[1];
		wait(50);
	}
	board_destroy(board);
	return 0;
}
