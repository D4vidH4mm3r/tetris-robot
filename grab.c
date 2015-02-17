#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "Board.h"

void get_pixel_color (Display *d, int x, int y, XColor *color) {
	XImage *image;
	image = XGetImage(d, RootWindow (d, DefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
	color->pixel = XGetPixel(image, 0, 0);
	XFree (image);
	XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), color);
}

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

int main(int argc, char const *argv[]) {
	int w_x=205;
	int n_y=260;
	int e_x=459;
	int s_y=716;
	int numcols = 10;
	int numrows = 18;
	int xstep = (e_x - w_x)/numcols;
	int ystep = (s_y - n_y)/numrows;

	int **b = board_create();

	printf("Step sizes: %d and %d\n", xstep, ystep);
	XColor c;
	Display *display = XOpenDisplay(NULL);
	for (int row=0; row<numrows; row++) {
		int y = n_y + row*ystep + ystep/2;
		for (int col=0; col<numcols; col++) {
			int x = w_x + col*xstep + xstep/2;
			get_pixel_color(display, x, y, &c);
			b[row][col] = color_guess(&c);
		}
	}
	board_print(b);
	return 0;
}
