#pragma once

#include "../utils/types.h"

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
Mem *mem_new(u32 size);

/**
 * Frees the allocated memory.
 *
 * @param mem The memory.
 */
void mem_free(Mem *mem);

/**
 * Loads the contents of the binary file into
 * this memory.
 *
 * @param mem      The memory.
 * @param filename The path to the binary file.
 */
void mem_init(Mem *mem, cstr filename);
