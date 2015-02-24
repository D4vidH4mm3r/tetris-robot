#ifndef _interaction_h
#define _interaction_h

#ifdef _WIN32

#else

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <sys/time.h>

#include "common.h"
#include "Board.h"
#include "Block.h"
#include "AI.h"

typedef struct Corners_t {
	int north;
	int east;
	int south;
	int west;
} Corners;

typedef struct Point_t {
	int x;
	int y;
} Point;

XImage *take_some_image(Corners c, Display *d);
Color guess_color_area(Corners c, Display *d);
Color color_guess(XColor *c);
void copy_to_board(Corners c, Display *d, Board board);
void move_send(Move *move, Display *d);
void wait(unsigned long msec);

#endif
#endif
