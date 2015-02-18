#ifndef _common_def
#define _common_def

#define NEW(thing) malloc(sizeof(thing))

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

typedef enum {BLUE=1, TEAL, YELLOW, MAGENTA, GREEN, RED, WHITE} Color;
typedef char **Board;

#endif
