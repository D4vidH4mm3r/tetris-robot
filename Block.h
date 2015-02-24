#ifndef _block_h
#define _block_h

#include "common.h"
#include "Board.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Block_t {
	int nr; /* number of rotation */
	int w[4]; /* width of rotation */
	int offset[4]; /* shifts from left start */
	Color c;
	char m[4][4][4];
} Block;

int block_touches(Block *block, int rot, Board board, int row, int col);
int block_hits_row(Block *block, int rot, Board board, int col);
void block_addblock(Block *block, int rot, Board board, int row, int col);
void block_drop(Block *block, int rot, Board board, int col);
void color_print(Color c);
Block block_I;
Block block_T;
Block block_O;
Block block_Z;
Block block_Zr;
Block block_L;
Block block_Lr;

#endif
