#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "dev/sdl/screen/screen.h"
#include "vm/vm.h"

// Allocate 64kB of memory.
u8 mem[0xffff];

// Allocate 16 device slots.
Device dev[15];

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
  screen.boot();

  // TODO: Read binary file into memory.
  // TODO: wird nicht benötigt.
  vm_boot(&vm, mem);
  vm_attach_device(&vm, 0, &screen);

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
      screen.halt();
      SDL_Quit();
      return EXIT_SUCCESS;

    default:
      vm_step(&vm);
      break;
    }
  }
  return EXIT_SUCCESS;
}
