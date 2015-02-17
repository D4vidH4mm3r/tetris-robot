#ifndef _board_h
#define _board_h

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int **board_create();
void board_copy(int **copy, int **board);
void board_print(int **board);
void board_destroy(int **board);
int board_collapse(int **board);
int board_dead(int **board);

#endif
