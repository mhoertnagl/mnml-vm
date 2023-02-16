#include <stdio.h>
#include <stdlib.h>
#include "nul.h"
#include "dev/dev.h"

static u8 boot()
{
  return EXIT_SUCCESS;
}

static u8 halt()
{
  return EXIT_SUCCESS;
}

static u16 read(u16 reg)
{
  return 0;
}

static void write(u16 reg, u16 value)
{
}

Device dev_nul = {
    .name = "dev/nul",
    .boot = boot,
    .halt = halt,
    .read = read,
    .write = write};