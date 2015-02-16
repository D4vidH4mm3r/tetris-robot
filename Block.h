#include "common.h"
#include "Board.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Block_t {
	int nr; /* number of rotation */
	int w[4]; /* width; last index w. 1 per rotation */
	Color c;
	char m[4][4][4];
} Block;

void block_addblock(Block *block, int r, int **board, int row, int col);
int  block_touches(Block *block, int **board);

void block_addblock(Block *block, int r, int **board, int row, int col) {
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			if (block->m[r][i][j]) {
				board[row+i][col+j] = block->c;
			}
		}
	}
}

Block block_I = {
	2,
	{3, 0, 0, 0},
	GREEN,
	{
		{
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0}}}
};
