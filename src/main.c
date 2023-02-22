#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "dev/dev.h"
#include "dev/sdl/screen/screen.h"
#include "vm/vm.h"

// Allocate 64kB of memory.
u8 mem[0xffff];

// Allocate 16 device slots.
Device *dev[DEV_MAX_ADDR];

// clang-format off
Vm vm = {
  .pc = 0,
  .sp = 0xffff,
  .mem = mem,
  .dev = dev,
};
// clang-format on

int main()
{
  Screen *screen = screen_create();

  dev_boot(screen);

  // TODO: Read binary file into memory.
  // TODO: wird nicht benötigt.
  vm_boot(&vm, mem);
  vm_attach_device(&vm, 0, screen);

  dev_write(screen, SCREEN_COLOR_RED, 0x00);
  dev_write(screen, SCREEN_COLOR_GREEN, 0xff);
  dev_write(screen, SCREEN_COLOR_BLUE, 0x00);
  dev_write(screen, SCREEN_COLOR_ALPHA, 0xff);

  for (int i = 0; i < 800; ++i)
  {
    dev_write(screen, SCREEN_POSITION_X, i);
    dev_write(screen, SCREEN_POSITION_Y, i);
    dev_write(screen, SCREEN_DRAW, 0);
  }
  dev_write(screen, SCREEN_RENDER, 0);

  SDL_Event e;
  while (1)
  {
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT)
    {
      return EXIT_SUCCESS;
    }

    // switch (e.type)
    // {
    // case SDL_QUIT:
    //   dev_destroy(screen);
    //   SDL_Quit();
    //   return EXIT_SUCCESS;

    // default:
    //   vm_step(&vm);
    //   break;
    // }
  }

  dev_destroy(screen);
  SDL_Quit();

  return EXIT_SUCCESS;
}
