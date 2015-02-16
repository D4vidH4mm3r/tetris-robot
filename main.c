#include "Block.h"

int main(void) {
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			printf("%d", block_I.m[1][i][j]);
		}
		printf("\n");
	}
	return 0;
}
