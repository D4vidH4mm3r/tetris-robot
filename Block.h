#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef Row Rotation[4];

typedef struct Block_t {
	int nr; /* number of rotation */
	Color c;
	char m[4][4][4];
} Block;

Block block_I = {
	2,
	GREEN,
	{
		{
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
		},
		{{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0}}}
};
