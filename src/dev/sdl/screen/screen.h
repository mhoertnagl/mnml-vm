#ifndef SCREEN_H
#define SCREEN_H

#include "dev/dev.h"

// clang-format off
#define SCREEN_COLOR_RED   0x0
#define SCREEN_COLOR_GREEN 0x1
#define SCREEN_COLOR_BLUE  0x2
#define SCREEN_COLOR_ALPHA 0x3
#define SCREEN_POSITION_X  0x4
#define SCREEN_POSITION_Y  0x5
#define SCREEN_DRAW        0x6
#define SCREEN_RENDER      0x7
// clang-format on

extern Device screen;

#endif