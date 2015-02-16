#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int board_collapse(Board *b);
Board *board_copy(Board *b);
void board_print(Board *b);
Board *board_create();
char *board_horizontal_edge;

Board *board_create() {
	Board *b = NEW(Board);
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			*b[row][col] = 0;
		}
	}
	return b;
}

void board_print(Board *b) {
	for (int i=0; i<BOARD_WIDTH+2; i++) {
		printf("_");
	}
	printf("\n");
	for (int row=0; row<BOARD_HEIGHT; row++) {
		printf("|");
		for (int col=0; col<BOARD_WIDTH; col++) {
			printf("%d", *b[row][col]);
		}
		printf("|\n");
	}
	for (int i=0; i<BOARD_WIDTH+2; i++) {
		printf("‾");
	}
	printf("\n");
}
