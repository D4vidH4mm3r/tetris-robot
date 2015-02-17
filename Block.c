#include "Block.h"

void block_addblock(Block *block, int rot, int **board, int row, int col) {
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			if (block->m[rot][i][j]) {
				board[row+i][col+j] = block->c;
			}
		}
	}
}

int block_touches(Block *block, int rot, int **board, int row, int col) {
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			if (block->m[rot][i][j] && (i+row+1>=BOARD_HEIGHT || board[i+row+1][col+j])) {
				return 1;
			}
		}
	}
	return 0;
}

int block_hits_row(Block *block, int rot, int **board, int col) {
	int row = 0;
	while (!block_touches(block, rot, board, row, col)) {
		row++;
	}
	return row;
}

void block_drop(Block *block, int rot, int **board, int col) {
	block_addblock(block, rot, board,
			block_hits_row(block, rot, board, col),
			col);
}

Block block_I = {
	2,
	{4, 1, 0, 0},
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

Block block_T = {
	4,
	{3, 2, 3, 2},
	RED,
	{
		{
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{0,0,0,0},
		},
		{
			{1,1,1,0},
			{0,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{0,0,0,0}
		}
	}
};

Block block_L = {
	4,
	{2, 3, 2, 3},
	MAGENTA,
	{
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0},
		},
		{
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,0,0,0},
		},
		{
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		}
	}
};

Block block_Lr = {
	4,
	{2, 3, 2, 3},
	BLUE,
	{
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
		},
		{
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0},
			{0,0,0,0},
		},
		{
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0},
			{0,0,0,0}
		}
	}
};

Block block_O = {
	1,
	{2, 0, 0, 0},
	YELLOW,
	{
		{
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
	}
};

Block block_Z = {
	2,
	{3, 2, 0, 0},
	WHITE,
	{
		{
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{0,0,0,0}}}
};

Block block_Zr = {
	2,
	{3, 2, 0, 0},
	TEAL,
	{
		{
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,0,0,0}}}
};
