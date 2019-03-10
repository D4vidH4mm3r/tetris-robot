#include <chrono>
#include <thread>
#include <random>

#include "Board.hpp"
#include "Block.h"
#include "AI.hpp"

int main(int argc, char const *argv[]) {
  long to_place = 2000L;
  if (argc > 1) {
    to_place = atol(argv[1]);
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(0, 6);

  Board board;
  int cleared = 0;

  Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
  Block *queue = (Block*)malloc(2*sizeof(Block));
  queue[0] = *blocks[uni(rng)];

  for (long i=0; i<to_place; i++) {
    queue[1] = *blocks[uni(rng)];
    std::cout << board << std::endl;
    for (int bi=0; bi<4; ++bi) {
      for (int preview=0; preview<2; ++preview) {
        for (int bj=0; bj<4; ++bj) {
          std::cout << brickToString(queue[preview].m[0][bi][bj]);
        }
      }
      std::cout << std::endl;
    }

    Move best = move_best_lookahead(board, &queue[0], &queue[1]);
    std::cout << "Best loc/rot: " << best.col << "/" << best.rot << std::endl;
    best.execute(board);

    if (board.dead()) {
      std::cout << board << std::endl;
      printf("%d cleared\n", cleared);
      printf("Dead :(\n");
      break;
    }
    cleared += board.collapse();

    queue[0] = queue[1];
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << board << std::endl;
  printf("%d cleared\n", cleared);
  free(queue);
  return 0;
}
