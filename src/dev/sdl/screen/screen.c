#include <stdlib.h>
#include <SDL2/SDL.h>
#include "screen.h"
#include "dev/dev.h"
#include "utils/bits.h"

#define WINDOW_TITLE "mnml VM v0.1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 640

typedef struct ScreenMemory
{
  u16 red;
  u16 green;
  u16 blue;
  u16 alpha;
  u16 x;
  u16 y;
} ScreenMemory;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

ScreenMemory mem;

static u8 boot()
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
      &window,
      &renderer);

  if (status == -1)
  {
    perror("Faild to create window and renderer.\n");
    perror(SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_SetWindowTitle(window, WINDOW_TITLE);

  return EXIT_SUCCESS;
}

static u8 halt()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  return EXIT_SUCCESS;
}

static u16 read(u16 reg)
{
  return EXIT_SUCCESS;
}

static void write(u16 reg, u16 val)
{
  switch (reg)
  {
  case SCREEN_COLOR_RED:
  {
    mem.red = val;
    SDL_SetRenderDrawColor(
        renderer,
        mem.red,
        mem.green,
        mem.blue,
        mem.alpha);
    break;
  }
  case SCREEN_COLOR_GREEN:
  {
    mem.green = val;
    SDL_SetRenderDrawColor(
        renderer,
        mem.red,
        mem.green,
        mem.blue,
        mem.alpha);
    break;
  }
  case SCREEN_COLOR_BLUE:
  {
    mem.blue = val;
    SDL_SetRenderDrawColor(
        renderer,
        mem.red,
        mem.green,
        mem.blue,
        mem.alpha);
    break;
  }
  case SCREEN_COLOR_ALPHA:
  {
    mem.alpha = val;
    SDL_SetRenderDrawColor(
        renderer,
        mem.red,
        mem.green,
        mem.blue,
        mem.alpha);
    break;
  }
  case SCREEN_POSITION_X:
  {
    mem.x = val;
    break;
  }
  case SCREEN_POSITION_Y:
  {
    mem.y = val;
    break;
  }
  case SCREEN_DRAW:
  {
    SDL_RenderDrawPoint(renderer, mem.x, mem.y);
    break;
  }
  case SCREEN_RENDER:
  {
    SDL_RenderPresent(renderer);
    break;
  }
  }
}

// clang-format off
Device screen = {
  .name  = "dev/sdl/screen",
  .boot  = boot,
  .halt  = halt,
  .read  = read,
  .write = write
};
// clang-format on
