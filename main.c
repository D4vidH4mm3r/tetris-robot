#include "Block.h"

enum blocks {L, Lm, Z, Zm, T, O, I};

int main(void) {
	Block Blocks[7];

	Blocks[O] = makeBlock(1, (Point []) {
		POINT(3,2), POINT(3,3), POINT(4,3), POINT(4,2)
	},
	"\x1B[33m#\x1B[0m");

	Blocks[I] = makeBlock(2, (Point []) {
			POINT(2,3), POINT(3,3), POINT(4,3), POINT(5,3),
			POINT(5,0), POINT(5,1), POINT(5,2), POINT(5,3),
			},
			"\x1B[36m#\x1B[0m");

	Blocks[Z] = makeBlock(2, (Point []) {
			POINT(4,3), POINT(5,3), POINT(5,2), POINT(6,2),
			POINT(5,1), POINT(5,2), POINT(6,2), POINT(6,3),
			},
			"\x1B[31m#\x1B[0m");

	Blocks[Zm] = makeBlock(2, (Point []) {
			POINT(3,2), POINT(4,2), POINT(4,3), POINT(5,3),
			POINT(4,3), POINT(4,2), POINT(5,2), POINT(5,1),
			},
			"\x1B[32m#\x1B[0m");

	Blocks[L] = makeBlock(4, (Point []) {
			POINT(2,2), POINT(3,2), POINT(4,2), POINT(4,3),
			POINT(3,3), POINT(3,2), POINT(3,1), POINT(4,1),
			POINT(2,2), POINT(2,3), POINT(3,3), POINT(4,3),
			POINT(2,2), POINT(3,2), POINT(4,2), POINT(4,1),
			},
			"\x1B[35m#\x1B[0m");

	Blocks[Lm] = makeBlock(4, (Point []) {
			POINT(3,3), POINT(3,2), POINT(4,2), POINT(5,2),
			POINT(4,3), POINT(3,3), POINT(3,2), POINT(3,1),
			POINT(4,2), POINT(2,3), POINT(3,3), POINT(4,3),
			POINT(2,1), POINT(3,1), POINT(3,2), POINT(3,3),
			},
			"\x1B[34m#\x1B[0m");

	Blocks[T] = makeBlock(4, (Point []) {
			POINT(3,2), POINT(4,2), POINT(5,2), POINT(4,3),
			POINT(4,1), POINT(4,2), POINT(4,3), POINT(5,2),
			POINT(3,2), POINT(4,2), POINT(5,2), POINT(4,1),
			POINT(4,1), POINT(4,2), POINT(4,3), POINT(3,2),
			},
			"\x1B[35m#\x1B[0m");

	return 0;
}
