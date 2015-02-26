#include "Interaction.h"

int main(int argc, char const *argv[]) {

	Point curr_block = {621, 416};
	Point next_block = {984, 507};
	Point NW = {398, 410};
	Point SE = {848, 1220};

	Board board = board_create();

	Color first = 0;
	Color next;
	while (!first) {
		first = color_at_point(curr_block);
	}
	color_print(first);

	while (1) {
		next = color_at_point(next_block);
		RGBColor testc = get_color(next_block);

		copy_to_board(board, NW, SE, BOARD_HEIGHT-2);
		board_print(board);

		Sleep(200);
	}
	board_destroy(board);
	return 0;
}
