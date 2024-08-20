#include <stdlib.h>
#include "nul.h"

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
  .boot = (boot_fn)boot,
  .halt = (halt_fn)halt,
  .read = (read_fn)read,
  .write = (write_fn)write
};