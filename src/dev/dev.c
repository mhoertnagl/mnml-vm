#include "dev.h"

u8 dev_boot(Device *dev)
{
  return dev->boot(dev);
}

u8 dev_halt(Device *dev)
{
  return dev->halt(dev);
}

u16 dev_read(Device *dev, u16 reg)
{
  return dev->read(dev, reg);
}

void dev_write(Device *dev, u16 reg, u16 val)
{
  dev->write(dev, reg, val);
}
