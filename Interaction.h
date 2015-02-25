#ifndef _interaction_h
#define _interaction_h

#include <Windows.h>
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
	int green;
	int blue;
} RGBColor;


RGBColor get_color(Point p);
Color guess_color(RGBColor c);
Color color_at_point(Point p);
void copy_to_board(Board board, Point NW, Point SE, int lines);
void move_send(Move *move);

#endif
