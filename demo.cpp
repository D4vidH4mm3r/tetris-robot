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

  Board b;
  int cleared = 0;

  Block *blocks[7] = {&block_O, &block_I, &block_L, &block_Lr, &block_Z, &block_Zr, &block_T};
  Block *queue = (Block*)malloc(2*sizeof(Block));
  queue[0] = *blocks[uni(rng)];

  for (long i=0; i<to_place; i++) {
    queue[1] = *blocks[uni(rng)];

    Move *best = move_best_lookahead(b, &queue[0], &queue[1]);
    std::cout << "Dropping " << queue[0].c << std::endl;
    std::cout << "Best loc/rot: " << best->col << "/" << best->rot << std::endl;
    move_execute(best, b);
    move_destroy(best);
    std::cout << b << std::endl;

    /*
    if (board_dead(b)) {
      std::cout << b << std::endl;
      printf("%d cleared\n", cleared);
      printf("Dead :(\n");
      b = board_create();
    }
    */
    cleared += b.collapse();

    queue[0] = queue[1];
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  std::cout << b << std::endl;
  printf("%d cleared\n", cleared);
  free(queue);
  return 0;
}
