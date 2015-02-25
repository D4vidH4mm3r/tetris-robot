#ifndef _interaction_h
#define _interaction_h

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

typedef struct RGBColor_t {
	int red;
	int blue;
	int green;
} RGBColor;

#ifdef _WIN32

#include <Windows.h>
typedef int WMconnection;

#else

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <sys/time.h>
typedef Display WMconnection;

#endif

WMconnection *setup_interaction();
RGBColor get_color(Point p, WMconnection *d);
Color guess_color(RGBColor c);
Color color_at_point(Point p, WMconnection *d);
void copy_to_board(Corners c, WMconnection *d, Board board);
void move_send(Move *move, WMconnection *d);
void wait(unsigned long msec);

#endif
