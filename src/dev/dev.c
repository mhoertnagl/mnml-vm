#include <stdlib.h>
#include "dev/dev.h"

void dev_destroy(Device *dev)
{
  dev->halt(dev->state);
  free(dev->state);
  free(dev);
}