#include <stdlib.h>
#include <SDL2/SDL.h>
#include "screen.h"
#include "dev/dev.h"
#include "utils/bits.h"

#define WINDOW_TITLE "mnml VM v0.1"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 640

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

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
  // TODO: Won't work anymore for 16bit vm.
  switch (reg)
  {
  case SCREEN_COLOR:
  {
    const u8 r = u8_hh(val);
    const u8 g = u8_hl(val);
    const u8 b = u8_lh(val);
    const u8 a = u8_ll(val);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    break;
  }
  case SCREEN_POSITION:
  {
    const u16 x = u16_h(val);
    const u16 y = u16_l(val);
    SDL_RenderDrawPoint(renderer, x, y);
    break;
  }
  case SCREEN_RENDER:
  {
    SDL_RenderPresent(renderer);
    break;
  }
  }
}

Device screen = {
    .name = "dev/sdl/screen",
    .boot = boot,
    .halt = halt,
    .read = read,
    .write = write};
