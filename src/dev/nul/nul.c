#include <stdio.h>
#include <stdlib.h>
#include "nul.h"
#include "dev/dev.h"

static u8 boot(Device *dev)
{
  return EXIT_SUCCESS;
}

static u8 halt(Device *dev)
{
  return EXIT_SUCCESS;
}

static u16 read(Device *dev, u16 reg)
{
  return 0;
}

static void write(Device *dev, u16 reg, u16 value)
{
}

Device dev_nul = {
    .name = "dev/nul",
    .boot = boot,
    .halt = halt,
    .read = read,
    .write = write};