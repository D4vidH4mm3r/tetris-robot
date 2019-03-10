#ifndef _ai_def
#define _ai_def

#include <cfloat>
#include "Board.hpp"

class Move {
public:
  const Block* block;
  int rot;
  int col;
  double score;
  void execute(Board& board) {
    board.block_drop(block, rot, col);
  };
  Move(Block* b) {
    block = b;
    rot = -1;
    col = -1;
    score = -DBL_MAX;
  }
  Move(Block* b, int r, int c) {
    block = b;
    rot = r;
    col = c;
    score = -DBL_MAX;
  }
};

typedef struct ScoreSet_t {
  int height_total;
  int height_max;
  int bumps;
  int cleared;
  int holes;
} ScoreSet;

void score_sweep(Board board, ScoreSet *score) {
  int col_height[BOARD_WIDTH] = {0};
  int holes = 0;
  for (int row=0; row<BOARD_HEIGHT; row++) {
    for (int col=0; col<BOARD_WIDTH; col++) {
      if (!col_height[col] && board.M[row][col]) {
        col_height[col] = BOARD_HEIGHT - row;
      } else if (col_height[col] && !board.M[row][col]) {
        holes++;
      }
    }
  }

  int height = 0;
  for (int col=0; col<BOARD_WIDTH; col++) {
    height += col_height[col];
  }

  int bumps = 0;
  for (int col=0; col<BOARD_WIDTH-1; col++) {
    bumps += abs(col_height[col] - col_height[col+1]);
  }

  score->bumps = bumps;
  score->height_total = height;
  score->holes = holes;
}

int score_cleared(Board board) {
  int cleared = 0;
  for (int row=0; row<BOARD_HEIGHT; row++) {
    int clears = 1;
    for (int col=0; col<BOARD_WIDTH; col++) {
      if (!board.M[row][col]) {
        clears = 0;
      }
    }
    if (clears) {
      cleared++;
    }
  }
  return cleared;
}

/* values from https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/ */
double score_total(Board board) {
  /* here, weighting is important; higher is better */
  ScoreSet score;
  score.cleared = score_cleared(board);
  score_sweep(board, &score);
  return score.cleared*0.99275
    + score.holes*(-0.46544)
    + score.height_total*(-0.66569)
    + score.bumps*(-0.24077);
}

int trycols(Block *b, int rot) {
  return BOARD_WIDTH - b->w[rot]+1;
}

Move move_best(Board board, Block *block) {
  Move bestMove(block);
  for (int rot=0; rot<block->nr; rot++) {
    int maxcol = trycols(block, rot);
    for (int col=0; col<maxcol; col++) {
      Board copy(board);
      copy.block_drop(block, rot, col);
      double score = score_total(copy);
      if (score > bestMove.score) {
        bestMove.score = score;
        bestMove.col = col;
        bestMove.rot = rot;
      }
    }
  }
  return bestMove;
}

std::vector<Move> all_moves(Block *block) {
  std::vector<Move> res;
  for (int rot=0; rot<block->nr; rot++) {
    int maxcol = trycols(block, rot);
    for (int col=0; col<maxcol; col++) {
      res.emplace_back(block, rot, col);
    }
  }
  return res;
}

Move move_best_lookahead(Board board, Block *current, Block *next) {
  std::vector<Move> firstMoves = all_moves(current);
  Move bestFirstMove(current);
  Move bestSecondMove(next);

  for (auto firstMove : firstMoves) {
    Board copy(board);
    firstMove.execute(copy);
    Move candidateSecondMove = move_best(copy, next);
    if (candidateSecondMove.score > bestSecondMove.score) {
      bestSecondMove = candidateSecondMove;
      bestFirstMove = firstMove;
    }
  }
  return bestFirstMove;
}

#endif
