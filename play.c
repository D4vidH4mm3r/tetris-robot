#include "Interaction.h"
#define STACKING 0
#define BETWEEN_CHECKS 10
#define CHECK_START 1
#define CHECK_REPEATEDLY 1

int main(int argc, char const *argv[]) {

	Point curr_block = {902, 554};
	Point next_block = {1110, 606};
	Point NW = {772, 550};
	Point SE = {1032, 1018};

	Board board = board_create();

	Block *blocks[8] = {NULL, &block_Lr, &block_Zr, &block_O, &block_L, &block_I, &block_T, &block_Z};
	Block *queue[2] = {0, 0};

	Color first = 0;
	Color next;
	while (!first) {
		first = color_at_point(curr_block);
	}
	queue[0] = blocks[first];

#if CHECK_START
	copy_to_board(board, NW, SE, 9);
#endif
	board_print(board);

#if CHECK_REPEATEDLY
	int check_board = BETWEEN_CHECKS;
#endif

#if STACKING
	ai_build_up = 1;
#endif

	ScoreSet score;

	Sleep(100);
	while (1) {
		next = color_at_point(next_block);
		RGBColor testc = get_color(next_block);
		queue[1] = blocks[next];

#if CHECK_REPEATEDLY
		check_board--;
		if (check_board == 0) {
			Sleep(30);
			copy_to_board(board, NW, SE, BOARD_HEIGHT);
			board_print(board);
			check_board = BETWEEN_CHECKS;
		}
#endif

		Move *best = move_best_lookahead(board, queue[0], queue[1]);
		move_execute(best, board);
		move_send(best);
		move_destroy(best);
		board_collapse(board);

#if STACKING
		score_sweep(board, &score);
		if (score.height_total > 90-score.holes) {
			printf("Switching to destroy\n");
			ai_build_up = 0;
		} else if (score.height_total < 15) {
			printf("Switching to build\n");
			ai_build_up = 1;
		}
#endif

		queue[0] = queue[1];
		Sleep(60);
	}

	board_destroy(board);
	return 0;
}
