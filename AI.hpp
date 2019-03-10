#ifndef _ai_def
#define _ai_def

#include <stdio.h>
#include <float.h>
#include "common.h"
#include "Board.hpp"

typedef struct Move_t {
  Block *block;
  double value;
  int rot;
  int col;
  struct Move_t *prev;
} Move;

typedef struct MoveSet_t {
  Block *block;
  int length;
  Move *moves;
} MoveSet;

void move_copy(Move *to, Move *from) {
  to->block = from->block;
  to->value = from->value;
  to->rot   = from->rot;
  to->col   = from->col;
  to->prev  = from->prev;
}

void move_destroy(Move *move) {
  free(move);
}

void moveset_destroy(MoveSet *moves) {
  free(moves->moves);
  free(moves);
}

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

void move_execute(Move *move, Board& board) {
  board.block_drop(move->block, move->rot, move->col);
}

int trycols(Block *b, int rot) {
  return BOARD_WIDTH - b->w[rot]+1;
}

Move *move_best(Board board, Block *block) {
  Move *best = new Move;
  best->value = -DBL_MAX;
  best->block = block;
  for (int rot=0; rot<block->nr; rot++) {
    int maxcol = trycols(block, rot);
    for (int col=0; col<maxcol; col++) {
      Board copy(board);
      copy.block_drop(block, rot, col);
      double score = score_total(copy);
      if (score > best->value) {
        best->value = score;
        best->col = col;
        best->rot = rot;
      }
    }
  }
  return best;
}

MoveSet *move_all(Block *block) {
  /* NOTE: angiver ikke korrekt value */
  MoveSet *ms = new MoveSet;
  int length = 0;

  for (int rot=0; rot<block->nr; rot++) {
    int maxcol = trycols(block, rot);
    length += maxcol;
  }

  ms->length = length;
  ms->moves = (Move*)malloc(length*sizeof(Move));
  ms->block = block;

  int moveno = 0;
  for (int rot=0; rot<block->nr; rot++) {
    int maxcol = trycols(block, rot);
    for (int col=0; col<maxcol; col++) {
      Move *current = &ms->moves[moveno];
      current->col = col;
      current->rot = rot;
      current->block = block;
      current->value = 0;
      moveno++;
    }
  }
  return ms;
}

Move *move_best_lookahead(Board board, Block *current, Block *next) {
  MoveSet *first_moves = move_all(current); // all moves with first block
  Move *best = new Move; // best move with second block
  best->value = -DBL_MAX;
  best->block = next;

  for (int i=0; i<first_moves->length; i++) {
    Board copy(board);
    Move *current = &first_moves->moves[i];
    move_execute(current, copy);
    Move *best_next = move_best(copy, best->block);
    if (best_next->value > best->value) {
      move_copy(best, best_next);
      best->prev = current;
    }
    move_destroy(best_next);
  }

  move_copy(best, best->prev);
  moveset_destroy(first_moves);
  return best;
}

void move_print(Move *m) {
  printf("Rotate %d times and drop col %d for %f value\n", m->rot, m->col, m->value);
}

#endif
