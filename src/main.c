#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "dev/sdl/screen/screen.h"
#include "vm/vm.h"

int main()
{
  screen.boot();

  // screen.write(SCREEN_COLOR, 0x00ff00ff);

  // for (int i = 0; i < 800; ++i)
  //   screen.write(SCREEN_POSITION, (i << 16) | i);

  // screen.write(SCREEN_RENDER, 0);

  SDL_Event e;
  while (1)
  {
    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_QUIT:
      SDL_Quit();
      return EXIT_SUCCESS;

    default:
      break;
    }
  }

  screen.halt();

  return EXIT_SUCCESS;
}
