#include "Interaction.h"

#ifdef _WIN32
#else
WMconnection *setup_interaction() {
	WMconnection *res = XOpenDisplay(NULL);
	return res;
}
#endif

void wait(unsigned long msec) {
	struct timespec ts;
	ts.tv_sec=0;
	ts.tv_nsec=msec*1000000;
	nanosleep(&ts);
}

void move_send(Move *move, WMconnection *display) {
	/* xmodmap -pke er nyttig */
	unsigned int k_space = 65;
	unsigned int k_left = 113;
	unsigned int k_right = 114;
	unsigned int k_up = 111;
	int wait_down = 50;
	int wait_up = 50;

	/* rotate */
	for (int i=0; i<move->rot; i++) {
		XTestFakeKeyEvent(display, k_up, True, wait_down);
		XTestFakeKeyEvent(display, k_up, False, wait_up);
	}

	int moves_right = move->col - move->block->offset[move->rot];
	if (moves_right > 0) {
		for (int i=0; i<moves_right; i++) {
			XTestFakeKeyEvent(display, k_right, True, wait_down);
			XTestFakeKeyEvent(display, k_right, False, wait_up);
		}
	} else {
		for (int i=0; i<(-moves_right); i++) {
			XTestFakeKeyEvent(display, k_left, True, wait_down);
			XTestFakeKeyEvent(display, k_left, False, wait_up);
		}
	}
	XTestFakeKeyEvent(display, k_space, True, wait_down);
	XTestFakeKeyEvent(display, k_space, False, wait_up);
	XFlush(display);
}

Color color_guess(WMcolor *c) {
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

XImage *take_some_image(Corners c, WMconnection *d) {
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

void copy_to_board(Corners c, WMconnection *d, Board board) {
	XImage *image = take_some_image(c, d);
	WMcolor color;

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

Color guess_color_area(Corners c, WMconnection *d) {
	XImage *image = take_some_image(c, d);
	WMcolor color;

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
