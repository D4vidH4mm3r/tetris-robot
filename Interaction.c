#include "Interaction.h"

void press_key(char key) {
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

RGBColor get_color(Point p) {
	HDC _hdc = GetDC(NULL);
	COLORREF _color = GetPixel(_hdc, p.x, p.y);
	ReleaseDC(NULL, _hdc);
	RGBColor res = {GetRValue(_color),
		GetGValue(_color),
		GetBValue(_color)};
	return res;
}

void move_send(Move *move) {
	/* rotate */
	switch (move->rot) {
		case 0:
			break;
		case 1:
			press_key('W');
			break;
		case 2:
			press_key('F');
			break;
		case 3:
			press_key('S');
			break;
	}

	int moves_right = move->col - move->block->offset[move->rot];
	if (moves_right > 0) {
		for (int i=0; i<moves_right; i++) { press_key('D'); }
	} else {
		for (int i=0; i<(-moves_right); i++) { press_key('A'); }
	}
	press_key('E');
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

Color color_at_point(Point p) {
	RGBColor c = get_color(p);
	return guess_color(c);
}
