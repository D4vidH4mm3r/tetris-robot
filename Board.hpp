#ifndef Board_hpp_h
#define Board_hpp_h

#include <algorithm>
#include <iostream>
#include <vector>
#include "Block.hpp"

class Board {
public:
  std::vector<std::vector<short> > M;
  Board(): M(BOARD_HEIGHT, std::vector<short>(BOARD_WIDTH)) {};

  void block_addblock(Block *block, int rot, int row, int col) {
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        if (block->m[rot][i][j]) {
          M[row+i][col+j] = block->m[rot][i][j];
        }
      }
    }
  }

  bool dead() {
    return std::any_of(M[0].begin(), M[0].end(), [](short v) {return v!=0;});
  }

  int block_touches(Block *block, int rot, int row, int col) {
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        if (block->m[rot][i][j] && (i+row+1>=BOARD_HEIGHT || M[i+row+1][col+j])) {
          return 1;
        }
      }
    }
    return 0;
  }

  int block_hits_row(Block *block, int rot, int col) {
    int row = 0;
    while (!block_touches(block, rot, row, col)) {
      row++;
    }
    return row;
  };

  int collapse() {
    int offset = 0;
    for (int row=BOARD_HEIGHT-1; row>=0; --row) {
      while (row-offset >= 0 && std::all_of(M[row-offset].begin(),
                                            M[row-offset].end(),
                                            [](short v) {return v!=0;})) {
        ++offset;
      }
      if (row-offset >= 0) {
        for (int col=0; col<BOARD_WIDTH; ++col) {
          M[row][col] = M[row-offset][col];
        }
      } else {
        for (int col=0; col<BOARD_WIDTH; ++col) {
          M[row][col] = 0;
        }
      }

    }
    return offset;
  };

  void block_drop(Block *block, int rot, int col) {
    block_addblock(block, rot, block_hits_row(block, rot, col), col);
  }
};

std::ostream& operator<< (std::ostream& os, const Board& b) {
  for (int row=0; row<BOARD_HEIGHT; ++row) {
    os << "|";
    for (int col=0; col<BOARD_WIDTH; ++col) {
      os << brickToString(b.M[row][col]);
    }
    os << "|\n";
  }
  return os;
}

#endif
