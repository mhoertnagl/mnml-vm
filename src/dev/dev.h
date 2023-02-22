#ifndef DEV_H
#define DEV_H

#include "utils/types.h"

/**
 * Device initialization function. This function will
 * be invoked once for this device at start-up.
 */
typedef u8 (*boot_fn)(void *dev);

/**
 * Device shut-down function. This function will be
 * invoked once for this device before the emulator
 * exits.
 */
typedef u8 (*halt_fn)(void *dev);

typedef u16 (*read_fn)(void *dev, u16 reg);
typedef void (*write_fn)(void *dev, u16 reg, u16 value);

/**
 *
 */
// clang-format off
typedef struct Device
{
  cstr     name;
  boot_fn  boot;
  halt_fn  halt;
  read_fn  read;
  write_fn write;
} Device;
// clang-format off

extern u8 dev_boot(Device *dev);

extern u8 dev_halt(Device *dev);

extern u16 dev_read(Device *dev, u16 reg);

extern void dev_write(Device *dev, u16 reg, u16 value);

extern void dev_destroy(Device *dev);

#endif