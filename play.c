#include "Interaction.h"

int main(int argc, char const *argv[]) {

	Point curr_block = {621, 416};
	Point next_block = {984, 507};
	Point NW = {398, 410};
	Point SE = {848, 1220};

	Board board = board_create();

	Block *blocks[8] = {NULL, &block_Lr, &block_Zr, &block_O, &block_L, &block_I, &block_T, &block_Z};
	Block *queue[2] = {0, 0};

	Color first = 0;
	Color next;
	while (!first) {
		first = color_at_point(curr_block);
	}
	queue[0] = blocks[first];
	copy_to_board(board, NW, SE, 9);
	board_print(board);

	int check_board = 10;
	ai_build_up = 1;
	Sleep(100);
	while (1) {
		next = color_at_point(next_block);
		RGBColor testc = get_color(next_block);
		queue[1] = blocks[next];

		//printf("Current:\n");
		//color_print(queue[0]->c);

		//printf("Next:\n");
		//color_print(queue[1]->c);
		//printf("---------\n");

		Move *best = move_best_lookahead(board, queue[0], queue[1]);
		//move_print(best);
		move_execute(best, board);
		move_send(best);
		move_destroy(best);
		board_collapse(board);
		if (check_board == 0) {
			Sleep(85);
			copy_to_board(board, NW, SE, BOARD_HEIGHT);
			board_print(board);
			check_board = 10;
		}
		if (score_height(board) > 60) {
			printf("destroy\n");
			ai_build_up = 0;
		} else if (score_height(board) < 25) {
			printf("build\n");
			ai_build_up = 1;
		}

		queue[0] = queue[1];
		check_board--;
		Sleep(85);
	}
	board_destroy(board);
	return 0;
}
