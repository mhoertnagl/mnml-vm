#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "vm.h"

static VmResult run(cstr filename) {
  u8 *code = mem_load(filename);
  return vm_run(code);
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  return run(argv[1]);
}

// #include <SDL2/SDL.h>
// #include "dev/dev.h"
// #include "dev/sdl/screen/screen.h"

// int run(cstr filename)
// {
//   Screen *screen = screen_new();

//   dev_boot(&screen->dev);

//   vm_attach_device(vm, 0, &screen->dev);

//   dev_write(&screen->dev, SCREEN_COLOR_RED, 0x00);
//   dev_write(&screen->dev, SCREEN_COLOR_GREEN, 0xff);
//   dev_write(&screen->dev, SCREEN_COLOR_BLUE, 0x00);
//   dev_write(&screen->dev, SCREEN_COLOR_ALPHA, 0xff);

//   for (int i = 0; i < 800; ++i)
//   {
//     dev_write(&screen->dev, SCREEN_POSITION_X, i);
//     dev_write(&screen->dev, SCREEN_POSITION_Y, i);
//     dev_write(&screen->dev, SCREEN_DRAW, 0);
//   }
//   dev_write(&screen->dev, SCREEN_RENDER, 0);

//   SDL_Event e;
//   while (1)
//   {
//     SDL_PollEvent(&e);

//     if (e.type == SDL_QUIT)
//     {
//       break;
//     }

//     vm_step(vm);
//   }

//   screen_free(screen);
//   mem_free(mem);
//   vm_free(vm);
//   SDL_Quit();

//   return EXIT_SUCCESS;
// }