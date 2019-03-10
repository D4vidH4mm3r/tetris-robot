#ifndef _block_h
#define _block_h

#include <iostream>
#include "common.hpp"

typedef struct Block_t {
  int nr; /* number of rotation */
  int w[4]; /* width of rotation */
  int offset[4]; /* shifts from left start */
  char m[4][4][4];
} Block;

std::ostream& operator<< (std::ostream& os, const Block& b) {
  for (int i=0; i<4; ++i) {
    for (int j=0; j<4; ++j) {
      os << brickToString(b.m[0][i][j]);
    }
    os << std::endl;
  }
  return os;
}

Block block_I = {
                 2,
                 {4, 1, 0, 0},
                 {3, 5, 0, 0},
                 {
                  {
                   {GREEN,GREEN,GREEN,GREEN},
                   {0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {GREEN,0,0,0},
                   {GREEN,0,0,0},
                   {GREEN,0,0,0},
                   {GREEN,0,0,0}}}
};

Block block_T = {
                 4,
                 {3, 2, 3, 2},
                 {3, 4, 3, 3},
                 {
                  {
                   {0,RED,0,0},
                   {RED,RED,RED,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {RED,0,0,0},
                   {RED,RED,0,0},
                   {RED,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {RED,RED,RED,0},
                   {0,RED,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {RED,0,0,0},
                   {RED,RED,0,0},
                   {RED,0,0,0},
                   {0,0,0,0}
                  }
                 }
};

Block block_L = {
                 4,
                 {3, 2, 3, 2},
                 {3, 4, 3, 3},
                 {
                  {
                   {0,0,MAGENTA,0},
                   {MAGENTA,MAGENTA,MAGENTA,0},
                   {0,0,0,0},
                   {0,0,0,0}
                  },
                  {
                   {MAGENTA,0,0,0},
                   {MAGENTA,0,0,0},
                   {MAGENTA,MAGENTA,0,0},
                   {0,0,0,0},
                  },
                  {
                   {MAGENTA,MAGENTA,MAGENTA,0},
                   {MAGENTA,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {MAGENTA,MAGENTA,0,0},
                   {0,MAGENTA,0,0},
                   {0,MAGENTA,0,0},
                   {0,0,0,0},
                  }
                 }
};

Block block_Lr = {
                  4,
                  {3, 2, 3, 2},
                  {3, 4, 3, 3},
                  {
                   {
                    {BLUE,0,0,0},
                    {BLUE,BLUE,BLUE,0},
                    {0,0,0,0},
                    {0,0,0,0},
                   },
                   {
                    {BLUE,BLUE,0,0},
                    {BLUE,0,0,0},
                    {BLUE,0,0,0},
                    {0,0,0,0},
                   },
                   {
                    {BLUE,BLUE,BLUE,0},
                    {0,0,BLUE,0},
                    {0,0,0,0},
                    {0,0,0,0}
                   },
                   {
                    {0,BLUE,0,0},
                    {0,BLUE,0,0},
                    {BLUE,BLUE,0,0},
                    {0,0,0,0},
                   },
                  }
};

Block block_O = {
                 1,
                 {2, 0, 0, 0},
                 {4, 0, 0, 0},
                 {
                  {
                   {YELLOW,YELLOW,0,0},
                   {YELLOW,YELLOW,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                 }
};

Block block_Z = {
                 2,
                 {3, 2, 0, 0},
                 {3, 4, 0, 0},
                 {
                  {
                   {WHITE,WHITE,0,0},
                   {0,WHITE,WHITE,0},
                   {0,0,0,0},
                   {0,0,0,0},
                  },
                  {
                   {0,WHITE,0,0},
                   {WHITE,WHITE,0,0},
                   {WHITE,0,0,0},
                   {0,0,0,0}}}
};

Block block_Zr = {
                  2,
                  {3, 2, 0, 0},
                  {3, 4, 0, 0},
                  {
                   {
                    {0,TEAL,TEAL,0},
                    {TEAL,TEAL,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                   },
                   {
                    {TEAL,0,0,0},
                    {TEAL,TEAL,0,0},
                    {0,TEAL,0,0},
                    {0,0,0,0}}}
};

#endif
