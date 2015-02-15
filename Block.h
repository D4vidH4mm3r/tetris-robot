#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef char Row[BOARD_WIDTH];
typedef Row Rotation[4];

typedef struct Block_t {
	int num_rotations;
	Rotation *rotations;
	char *string;
} Block;

typedef struct Point_t {
	int x;
	int y;
} Point;
#define POINT(x,y) (Point){x, y}

Block makeBlock(int num_rotations, Point points[], char *string);
void printBlock(Block, int rotation);

Block makeBlock(int num_rotations, Point points[], char *string) {
	Block *block = NEW(Block);
	block->num_rotations = num_rotations;
	block->rotations = calloc(num_rotations, sizeof(Rotation));
	block->string = malloc((strlen(string)+1)*sizeof(char));
	strcpy(block->string, string);

	for (int rotation=0; rotation<num_rotations; rotation++) {
		for (int part=0; part<4; part++) {
			Point curr = points[rotation*4+part];
			block->rotations[rotation][3-curr.y][curr.x] = 1;
		}
	}
	return *block;
}

void printBlock(Block block, int rotation) {
	for (int y=0; y<4; y++) {
		for (int x=0; x<BOARD_WIDTH; x++) {
			//printf("Reading rot %d y %d x %d\n", rotation, y, x);
			if (block.rotations[rotation][y][x]) {
				printf("%s", block.string);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}
