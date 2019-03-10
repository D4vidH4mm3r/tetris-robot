#ifndef _common_def
#define _common_def

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 18

typedef enum {BLUE=1, TEAL, YELLOW, MAGENTA, GREEN, RED, WHITE, GREY} Color;

std::string brickToString(short b) {
  if (b > 0) {
    switch (b) {
    case BLUE:
      return "\x1B[34m#\x1B[0m";
    case TEAL:
      return "\x1B[36m#\x1B[0m";
    case YELLOW:
      return "\x1B[33m#\x1B[0m";
    case MAGENTA:
      return "\x1B[35m#\x1B[0m";
    case GREEN:
      return "\x1B[32m#\x1B[0m";
    case RED:
      return "\x1B[31m#\x1B[0m";
    case WHITE:
      return "\x1B[37m#\x1B[0m";
    case GREY:
      return "\x1B[40m#\x1B[0m";
    default:
      return "!";
    }
  } else {
    return " ";
  }
}

#endif
