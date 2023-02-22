#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include "dev/dev.h"

// clang-format off
/** 
 * Red color channel device register address. 
 */
#define SCREEN_COLOR_RED   0x0

/** 
 * Green color channel device register address.
 */
#define SCREEN_COLOR_GREEN 0x1

/** 
 * Blue color channel device register address.
 */
#define SCREEN_COLOR_BLUE  0x2

/** 
 * Alpha channel device register address.
 */
#define SCREEN_COLOR_ALPHA 0x3

/** 
 * X position device register address. Origin is 
 * the top left corner.
 */
#define SCREEN_POSITION_X  0x4

/** 
 * Y position device register address. Origin is 
 * the top left corner.
 */
#define SCREEN_POSITION_Y  0x5

/** 
 * Draw to the screen at the currently specified 
 * position in the current color.
 */
#define SCREEN_DRAW        0x6

/**
 * Commits all changes to the screen.
 */
#define SCREEN_RENDER      0x7
// clang-format on

/**
 * SDL2 Screen device. Holds the current color
 * and position.
 */
typedef struct Screen
{
  // clang-format off
  Device       dev;
  SDL_Window   *window;
  SDL_Renderer *renderer;
  u16          red;
  u16          green;
  u16          blue;
  u16          alpha;
  u16          x;
  u16          y;
  // clang-format on
} Screen;

/**
 * Creates a new screen with color and
 * coordinates initialized to zero.
 *
 * @returns Pointer to the Screen device.
 */
extern Screen *screen_create();

#endif