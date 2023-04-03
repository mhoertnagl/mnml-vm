#ifndef DEV_H
#define DEV_H

#include "utils/types.h"

/**
 * Device initialization function. This function will
 * be invoked once for this device at start-up.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 */
typedef u8 (*boot_fn)(void *dev);

/**
 * Device shut-down function. This function will be
 * invoked once for this device before the emulator
 * exits.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 */
typedef u8 (*halt_fn)(void *dev);

/**
 * Reads the contents of the specified device register
 * address.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 * @param reg The device register address to read from.
 * @returns The value of the register.
 */
typedef u16 (*read_fn)(void *dev, u16 reg);

/**
 * Writes the specified value to the device register.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 * @param reg The device register address to write to.
 * @param val The value to write to the device register.
 */
typedef void (*write_fn)(void *dev, u16 reg, u16 val);

/**
 * Device struct. Contains meta information about this
 * device and function pointers the device's methods.
 */
typedef struct
{
  // clang-format off
  cstr     name;
  boot_fn  boot;
  halt_fn  halt;
  read_fn  read;
  write_fn write;
  // clang-format off
} Device;


/**
 * Device initialization function. This function will
 * be invoked once for this device at start-up.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 */
extern u8 dev_boot(Device *dev);

/**
 * Device shut-down function. This function will be
 * invoked once for this device before the emulator
 * exits.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 */
extern u8 dev_halt(Device *dev);

/**
 * Reads the contents of the specified device register
 * address.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 * @param reg The device register address to read from.
 * @returns The value of the register.
 */
extern u16 dev_read(Device *dev, u16 reg);

/**
 * Writes the specified value to the device register.
 *
 * @param dev A struct that implements the device
 *            struct as its first item.
 * @param reg The device register address to write to.
 * @param val The value to write to the device register.
 */
extern void dev_write(Device *dev, u16 reg, u16 val);

#endif