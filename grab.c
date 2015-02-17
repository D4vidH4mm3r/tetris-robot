#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "Board.h"
#include <unistd.h>

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
	Corners gameboard = {502, 341, 1058, 32};
	Corners curr_block = {502, 186, 533, 156};
	Corners next_block = {568, 438, 570, 436};

	Display *display = XOpenDisplay(NULL);

	while (1) {
		Color next = guess_color_area(next_block, display);
		Color curr = guess_color_area(curr_block, display);
		printf("Next, current:\n");
		color_print(next);
		color_print(curr);
		printf("---------\n");
	}
	return 0;
}
