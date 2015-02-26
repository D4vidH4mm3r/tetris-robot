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

	Sleep(12);
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
		for (int i=0; i<moves_right; i++) {
			press_key('D');
		}
	} else {
		for (int i=0; i<(-moves_right); i++) {
			press_key('A');
		}
	}
	press_key('E');
}

Color guess_color(RGBColor c) {
	int high = 160;
	int low  = 75;
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
				if (c.red > low && c.green > low && c.blue > low) {
					return GREY;
				} else {
					return 0;
				}
			}
		}
	}
}

Color color_at_point(Point p) {
	RGBColor c = get_color(p);
	return guess_color(c);
}

void copy_to_board(Board board, Point NW, Point SE, int lines) {
	/* entire board should be inside NW - SE
	 * lines is number of lines from bottom to copy */
	int by = (SE.y-NW.y)/BOARD_HEIGHT;
	int bx = (SE.x-NW.x)/BOARD_WIDTH;
	HDC _hdc = GetDC(NULL);
	for (int row=BOARD_HEIGHT-lines; row<BOARD_HEIGHT; row++) {
		for (int col=0; col<BOARD_WIDTH; col++) {
			int x = NW.x + col*bx + 0.5*bx;
			int y = NW.y + row*by + 0.5*by;
			COLORREF _color = GetPixel(_hdc, x, y);
			RGBColor color = {GetRValue(_color),
				GetGValue(_color),
				GetBValue(_color)};
			board[row][col] = guess_color(color);
		}
	}
	ReleaseDC(NULL, _hdc);
}
