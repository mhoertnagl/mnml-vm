#ifndef MEM_H
#define MEM_H

#include "utils/types.h"

/** Maximum size of addressable memory. */
#define MEM_SIZE_MAX 0xffff

typedef struct
{
  // clang-format off
  u8  *dat;
  u32 len;
  // clang-format on
} Mem;

/**
 * Allocate size bytes of memory.
 *
 * @param size The size of the memory
 *             in bytes.
 */
extern Mem *new_mem(u32 size);

/**
 * Frees the allocated memory.
 *
 * @param mem The memory.
 */
extern void free_mem(Mem *mem);

/**
 * Loads the contents of the binary file into
 * this memory.
 *
 * @param mem      The memory.
 * @param filename The path to the binary file.
 */
extern void mem_init(Mem *mem, cstr filename);

#endif