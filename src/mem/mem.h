#ifndef MEM_H
#define MEM_H

#include "utils/types.h"

/**
 * Maximum size of accessible memory.
 */
#define MEM_SIZE_MAX 0xffff

typedef struct Mem
{
  // clang-format off
  u8  *dat;
  u32 len;
  // clang-format on
} Mem;

/**
 * Allocate 64kb of memory.
 */
extern Mem *mem_create(u32 size);

/**
 * Loads the contents of the binary file into
 * this memory.
 *
 * @param mem      The memory.
 * @param filename The path to the binary file.
 */
extern void mem_init(Mem *mem, cstr filename);

extern void mem_destroy(Mem *mem);

#endif