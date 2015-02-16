#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int **board_create();
void board_copy(int **copy, int **board);
void board_print(int **board);
int board_collapse(int **board);

int **board_create() {
	int **b = malloc(BOARD_HEIGHT*sizeof(int *));
	for (int row=0; row<BOARD_HEIGHT; row++) {
		b[row] = malloc(BOARD_WIDTH*sizeof(int));
		for (int col=0; col<BOARD_WIDTH; col++) {
			b[row][col] = 0;
		}
	}
	return b;
}

void board_copy(int **copy, int **board) {
	for (int row=0; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			copy[row][col] = board[row][col];
		}
	}
}

void board_print(int **b) {
	for (int i=0; i<BOARD_WIDTH+2; i++) {
		printf("_");
	}
	printf("\n");
	for (int row=0; row<BOARD_HEIGHT; row++) {
		printf("|");
		for (int col=0; col<BOARD_WIDTH; col++) {
			printf("%d", b[row][col]);
		}
		printf("|\n");
	}
	for (int i=0; i<BOARD_WIDTH+2; i++) {
		printf("‾");
	}
	printf("\n");
}

int board_collapse(int **board) {
	int cleared = 0;
	for (int row=BOARD_HEIGHT-1; row>=0; row--) {
		int full=1;
		for (int col=0; col<BOARD_WIDTH; col++) {
			if (!board[row][col]) {
				full = 0;
			}
		}
		if (full) {
			cleared++;
			free(board[row]);
			for (int fall=row; fall>0; fall--) {
				board[fall] = board[fall-1];
			}
			board[0] = calloc(BOARD_WIDTH,sizeof(int));
		}
	}
	return cleared;
}
