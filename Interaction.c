#include "Interaction.h"

#ifdef _WIN32
WMconnection *setup_interaction() {
	FARPROC pGetPixel;
	HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
	pGetPixel = GetProcAddress(_hGDI, "GetPixel");
	return NULL; // nothing needed for now
}

void press_key(char key, WMconnection *d) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	Sleep(20);
	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(20);
	ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void wait(unsigned long msec) {
	Sleep(msec);
}

RGBColor get_color(Point p, WMconnection *d) {
	HDC _hdc = GetDC(NULL);
	COLORREF _color = (*pGetPixel, p.x, p.y);
	ReleaseDC(NULL, _hdc);
	RGBColor res = {GetRValue(_color),
		GetGValue(_color),
		GetBValue(_color)};
	return res;
}

#else

WMconnection *setup_interaction() {
	WMconnection *res = XOpenDisplay(NULL);
	return res;
}

void press_key(char key, WMconnection *d) {
	int keycode;
	switch (key) {
		// WASD
		case 'W':
			keycode=25;
			break;
		case 'A':
			keycode=38;
			break;
		case 'S':
			keycode=40;
			break;
		case 'D':
			keycode=42;
			break;
			// arrows and space
		case ' ':
			keycode=65;
			break;
		case 'l':
			keycode=113;
			break;
		case 'r':
			keycode=114;
			break;
		case 'u':
			keycode=111;
			break;
	}
	XTestFakeKeyEvent(d, keycode, True, 50);
	XTestFakeKeyEvent(d, keycode, False, 50);
	// XFlush(d); ?
}

RGBColor get_color(Point p, WMconnection *d) {
	XImage *image = XGetImage(d,
			RootWindow(d, DefaultScreen(d)),
			p.x,
			p.y,
			1,
			1,
			AllPlanes,
			XYPixmap);

	XColor color;

	color.pixel = XGetPixel(image, 0, 0);
	XQueryColor(d, DefaultColormap(d, DefaultScreen(d)), &color);
	XFree(image);
	RGBColor res = {color.red, color.green, color.blue};
	return res;
}

#endif

void wait(unsigned long msec) {
	struct timespec ts;
	ts.tv_sec=0;
	ts.tv_nsec=msec*1000000;
	nanosleep(&ts);
}

void move_send(Move *move, WMconnection *d) {
	/* rotate */
	for (int i=0; i<move->rot; i++) { press_key('W', d); }

	int moves_right = move->col - move->block->offset[move->rot];
	if (moves_right > 0) {
		for (int i=0; i<moves_right; i++) { press_key('D', d); }
	} else {
		for (int i=0; i<(-moves_right); i++) { press_key('A', d); }
	}
	press_key('S', d);
}

Color guess_color(RGBColor c) {
	int high = 98;
	if (c.red>high) {
		if (c.green>high) {
			if (c.blue>high) {
				return WHITE;
			} else {
				return YELLOW;
			}
		} else {
			/* red high, green not */
			if (c.blue>high) {
				return MAGENTA;
			} else {
				return RED;
			}
		}
	} else {
		/* red low */
		if (c.green>high) {
			if (c.blue>high) {
				return TEAL;
			} else {
				return GREEN;
			}
		} else {
			/* red, green low */
			if (c.blue>high) {
				return BLUE;
			} else {
				return 0;
			}
		}
	}
}

Color color_at_point(Point p, WMconnection *d) {
	RGBColor c = get_color(p, d);
	return guess_color(c);
}
