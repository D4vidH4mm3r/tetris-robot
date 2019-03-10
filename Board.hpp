#ifndef Board_hpp_h
#define Board_hpp_h

#include <algorithm>
#include <iostream>
#include <vector>
#include "common.h"
#include "Block.hpp"

class Board {
public:
  std::vector<std::vector<short> > M;
  Board(): M(BOARD_HEIGHT, std::vector<short>(BOARD_WIDTH)) {};

  void block_addblock(Block *block, int rot, int row, int col) {
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        if (block->m[rot][i][j]) {
          M[row+i][col+j] = block->c;
        }
      }
    }
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
  for (int row=0; row<b.M.size(); ++row) {
    os << "|";
    for (int col=0; col<b.M[row].size(); ++col) {
      if (b.M[row][col]) {
        switch (b.M[row][col]) {
        case BLUE:
          os << "\x1B[34m";
          break;
        case TEAL:
          os << "\x1B[36m";
          break;
        case YELLOW:
          os << "\x1B[33m";
          break;
        case MAGENTA:
          os << "\x1B[35m";
          break;
        case GREEN:
          os << "\x1B[32m";
          break;
        case RED:
          os << "\x1B[31m";
          break;
        case WHITE:
          os << "\x1B[37m";
          break;
        case GREY:
          os << "\x1B[40m";
          break;
        }
        os << "#\x1B[0m";
      } else {
        os << " ";
      }
    }
    os << "|\n";
  }
  return os;
}

#endif
