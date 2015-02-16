#ifndef _common_def
#define _common_def

#define NEW(thing) malloc(sizeof(thing))

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 12

typedef enum {BLUE=1, TEAL, YELLOW, PURPLE, GREEN, RED, WHITE} Color;

typedef char Row[BOARD_WIDTH];
typedef Row Board[BOARD_HEIGHT];

#endif
