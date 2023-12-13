#include <stdlib.h>
#include "screen.h"
// #include "dev/dev.h"

#define WINDOW_TITLE "mnml VM v0.1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

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
      WINDOW_HEIGHT,
      0,
      &screen->window,
      &screen->renderer);

  if (status == -1)
  {
    perror("Failed to create window and renderer.\n");
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

Screen *new_screen()
{
  // clang-format off
  Screen *screen    = malloc(sizeof(Screen));
  screen->dev.name  = "dev/sdl/screen";
  screen->dev.boot  = screen_boot;
  screen->dev.halt  = screen_halt;
  screen->dev.read  = screen_read;
  screen->dev.write = screen_write;
  screen->window    = NULL;
  screen->renderer  = NULL;
  screen->red       = 0;
  screen->green     = 0;
  screen->blue      = 0;
  screen->alpha     = 0;
  screen->x         = 0;
  screen->y         = 0;
  // clang-format on
  return screen;
}

void free_screen(Screen *screen)
{
  screen_halt(screen);
  free(screen);
}
