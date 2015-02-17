#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>

void get_pixel_color (Display *d, int x, int y, XColor *color) {
	XImage *image;
	image = XGetImage (d, RootWindow (d, DefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
	color->pixel = XGetPixel (image, 0, 0);
	XFree (image);
	XQueryColor (d, DefaultColormap(d, DefaultScreen (d)), color);
}

int main(int argc, char const *argv[]) {

	if (argc<3) {
		printf("Please specify x, y\n");
		return 1;
	}

	XColor c;
	Display *display = XOpenDisplay(NULL);
	get_pixel_color(display, atoi(argv[1]), atoi(argv[2]), &c);
	printf ("%d %d %d\n", c.red, c.green, c.blue);
	return 0;
}
