#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "dev/dev.h"
#include "dev/sdl/screen/screen.h"
#include "mem/mem.h"
#include "vm/vm.h"

int main(int argc, char **argv)
{
  if (argc < 1)
  {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  return run(argv[1]);
}

int run(cstr filename)
{
  Mem *mem = new_mem(MEM_SIZE_MAX);
  Screen *screen = new_screen();
  Vm *vm = new_vm();

  mem_init(mem, filename);
  dev_boot(screen);

  vm_attach_memory(vm, mem);
  vm_attach_device(vm, 0, screen);

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
      break;
    }

    vm_step(vm);
  }

  free_screen(screen);
  free_mem(mem);
  free_vm(vm);
  SDL_Quit();

  return EXIT_SUCCESS;
}