#include "AI.hpp"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void score_summary(Board board) {
  ScoreSet score;
  score.cleared = score_cleared(board);
  score_sweep(board, &score);
  //printf("Agg. height: %d, bumps: %d\n Cleared: %d, holes: %d\n Total: %f\n",
         //score.height_total, score.bumps, score.cleared, score.holes);
}

int main(void) {
  Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
  Board b;

  std::cout << b << std::endl;
  score_summary(b);

  b.block_drop(blocks[0], 0, 0);
  b.block_drop(blocks[0], 0, 2);
  b.block_drop(blocks[0], 0, 4);
  b.block_drop(blocks[0], 0, 6);
  b.block_drop(blocks[0], 0, 8);

  b.block_drop(blocks[0], 0, 0);
  b.block_drop(blocks[0], 0, 4);
  b.block_drop(blocks[1], 0, 0);
  b.block_drop(blocks[1], 0, 4);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  b.block_drop(blocks[0], 0, 8);
  std::cout << b << std::endl;
  std::cout << b.collapse() << std::endl;
  std::cout << b << std::endl;
  /*
  block_drop(blocks[0], 0, b, 2);
  block_drop(blocks[0], 0, b, 4);
  board_print(b);
  score_summary(b);
  block_drop(blocks[1], 1, b, 7);
  board_print(b);
  score_summary(b);
  block_drop(blocks[1], 0, b, 4);
  board_print(b);
  score_summary(b);
  */

  return 0;
}
