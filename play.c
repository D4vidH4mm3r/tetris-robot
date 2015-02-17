#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "Board.h"
#include "Block.h"
#include "AI.h"

Color color_guess(XColor *c) {
	int low = 8000;
	int mid = 20000;
	int high = 35000;
	if (c->red>high) {
		if (c->green>high) {
			if (c->blue>high) {
				return WHITE;
			} else {
				return YELLOW;
			}
		} else {
			/* red high, green not */
			if (c->blue>high) {
				return MAGENTA;
			} else {
				return RED;
			}
		}
	} else {
		/* red low */
		if (c->green>high) {
			if (c->blue>high) {
				return TEAL;
			} else {
				return GREEN;
			}
		} else {
			/* red, green low */
			if (c->blue>high) {
				return BLUE;
			} else {
				return 0;
			}
		}
	}
}

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

XImage *take_some_image(Corners c, Display *d) {
	XImage *image = XGetImage(d,
			RootWindow(d, DefaultScreen(d)),
			c.west,
			c.north,
			(c.east-c.west),
			(c.south-c.north),
			AllPlanes,
			XYPixmap);
	return image;
}

void copy_to_board(Corners c, Display *d, int **board) {
	XImage *image = take_some_image(c, d);
	XColor color;

	int xstep = (c.east - c.west)/BOARD_WIDTH;
	int ystep = (c.south - c.north)/BOARD_HEIGHT;

	for (int row=0; row<BOARD_HEIGHT; row++) {
		int y = row*ystep + ystep/2;

		for (int col=0; col<BOARD_WIDTH; col++) {
			int x = col*xstep + xstep/2;

			color.pixel = XGetPixel(image, x, y);
			XQueryColor(d, DefaultColormap(d, DefaultScreen(d)), &color);
			board[row][col] = color_guess(&color);
		}
	}
	XFree(image);
}

Color guess_color_area(Corners c, Display *d) {
	XImage *image = take_some_image(c, d);
	XColor color;

	int width = (c.east-c.west);
	int height = (c.south-c.north);

	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			color.pixel = XGetPixel(image, x, y);
			XQueryColor(d, DefaultColormap(d, DefaultScreen(d)), &color);
			Color guess = color_guess(&color);
			if (guess) {
				XFree(image);
				return guess;
			}
		}
	}
	XFree(image);
	return 0;
}

Point center(Corners c) {
	Point res = {
		c.west  + (c.east-c.west)/2,
		c.north + (c.south-c.north)/2
	};
}

void color_print(Color c) {
	switch (c) {
		case TEAL:
			printf("TEAL\n");
			break;
		case RED:
			printf("RED\n");
			break;
		case BLUE:
			printf("BLUE\n");
			break;
		case MAGENTA:
			printf("MAGENTA\n");
			break;
		case GREEN:
			printf("GREEN\n");
			break;
		case YELLOW:
			printf("YELLOW\n");
			break;
		case WHITE:
			printf("WHITE\n");
			break;
		default:
			printf("None...\n");
	}
}

int main(int argc, char const *argv[]) {
	Corners curr_block = {218, 1792, 237, 1776};
	Corners next_block = {260, 1975, 264, 1971};

	Display *display = XOpenDisplay(NULL);

	Block *blocks[8] = {NULL, &block_Lr, &block_Zr, &block_O, &block_L, &block_I, &block_T, &block_Z};
	Block *queue[2] = {0, 0};

	Color first = 0;
	Color next;
	while (!first) {
		first = guess_color_area(curr_block, display);
	}
	queue[0] = blocks[first];

	while (1) {
		next = guess_color_area(next_block, display);
		queue[1] = blocks[next];

		printf("Current:\n");
		color_print(queue[0]->c);

		printf("Next:\n");
		color_print(queue[1]->c);

		printf("---------\n");

		queue[0] = queue[1];
		getchar();
	}
	return 0;
}
