#ifndef DEV_H
#define DEV_H

#include "utils/types.h"

/**
 * Device initialization function. This function will
 * be invoked once for this device at start-up.
 */
typedef u8 (*boot_fn)(void *state);

/**
 * Device shut-down function. This function will be
 * invoked once for this device before the emulator
 * exits.
 */
typedef u8 (*halt_fn)(void *state);

typedef u16 (*read_fn)(void *state, u16 reg);
typedef void (*write_fn)(void *state, u16 reg, u16 value);

/**
 *
 */
// clang-format off
typedef struct Device
{
  cstr     name;
  void     *state;
  boot_fn  boot;
  halt_fn  halt;
  read_fn  read;
  write_fn write;
} Device;
// clang-format off

extern void dev_destroy(Device *dev);

#endif