#ifndef _board_h
#define _board_h

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

Board board_create();
void board_copy(Board copy, Board board);
void board_print(Board board);
void board_destroy(Board board);
int board_collapse(Board board);
int board_dead(Board board);

#endif
