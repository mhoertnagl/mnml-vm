#include <stdlib.h>
#include "screen.h"
// #include "dev/dev.h"

#define WINDOW_TITLE "mnml VM v0.1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 640

static u8 screen_boot(Screen *screen)
{
  // Attempt to initialize the SDL video subsystem.
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    perror("Could not initialize SDL video mode.\n");
    perror(SDL_GetError());
    return EXIT_FAILURE;
  }

  // Create a new window of size 800x640 centered at the
  // screen and a renderer to draw pixels.
  int status = SDL_CreateWindowAndRenderer(
      WINDOW_WIDTH,
      WINDOW_HEIGTH,
      0,
      &screen->window,
      &screen->renderer);

  if (status == -1)
  {
    perror("Faild to create window and renderer.\n");
    perror(SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_SetWindowTitle(screen->window, WINDOW_TITLE);

  return EXIT_SUCCESS;
}

static u8 screen_halt(Screen *screen)
{
  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
  return EXIT_SUCCESS;
}

static u16 screen_read(Screen *screen, u16 reg)
{
  return EXIT_SUCCESS;
}

static void screen_write(Screen *screen, u16 reg, u16 val)
{
  switch (reg)
  {
  case SCREEN_COLOR_RED:
  {
    screen->red = val;
    SDL_SetRenderDrawColor(
        screen->renderer,
        screen->red,
        screen->green,
        screen->blue,
        screen->alpha);
    break;
  }
  case SCREEN_COLOR_GREEN:
  {
    screen->green = val;
    SDL_SetRenderDrawColor(
        screen->renderer,
        screen->red,
        screen->green,
        screen->blue,
        screen->alpha);
    break;
  }
  case SCREEN_COLOR_BLUE:
  {
    screen->blue = val;
    SDL_SetRenderDrawColor(
        screen->renderer,
        screen->red,
        screen->green,
        screen->blue,
        screen->alpha);
    break;
  }
  case SCREEN_COLOR_ALPHA:
  {
    screen->alpha = val;
    SDL_SetRenderDrawColor(
        screen->renderer,
        screen->red,
        screen->green,
        screen->blue,
        screen->alpha);
    break;
  }
  case SCREEN_POSITION_X:
  {
    screen->x = val;
    break;
  }
  case SCREEN_POSITION_Y:
  {
    screen->y = val;
    break;
  }
  case SCREEN_DRAW:
  {
    SDL_RenderDrawPoint(
        screen->renderer,
        screen->x,
        screen->y);
    break;
  }
  case SCREEN_RENDER:
  {
    SDL_RenderPresent(screen->renderer);
    break;
  }
  }
}

// clang-format off
// Device screen_dev = {
//   .name  = "dev/sdl/screen",
//   .boot  = screen_boot,
//   .halt  = screen_halt,
//   .read  = screen_read,
//   .write = screen_write
// };
// clang-format on

// clang-format off
Device *screen_create()
{
  Screen *state   = malloc(sizeof(Screen));
  state->window   = NULL;
  state->renderer = NULL;
  state->red      = 0;
  state->green    = 0;
  state->blue     = 0;
  state->alpha    = 0;
  state->x        = 0;
  state->y        = 0;

  Device *dev      = malloc(sizeof(Device));
  dev->name        = "dev/sdl/screen";
  dev->state       = state;
  dev->boot        = screen_boot;
  dev->halt        = screen_halt;
  dev->read        = screen_read;
  dev->write       = screen_write;

  return dev;
}
// clang-format on

// // clang-format off
// Screen screen = {
//   .dev = {
//     .name  = "dev/sdl/screen",
//     .boot  = screen_boot,
//     .halt  = screen_halt,
//     .read  = screen_read,
//     .write = screen_write
//   },
//   .window = NULL,
//   .renderer = NULL,
//   .red = 0,
//   .green = 0,
//   .blue = 0,
//   .alpha = 0,
//   .x = 0,
//   .y = 0,
// };
// // clang-format on

// // clang-format off
// Device screen = {
//   .name  = "dev/sdl/screen",
//   .boot  = screen_boot,
//   .halt  = screen_halt,
//   .read  = screen_read,
//   .write = screen_write
// };
// // clang-format on
