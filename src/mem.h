#pragma once

#include <stdint.h>

typedef const char * cstr;
typedef uint8_t u8;

/**
 * Loads the contents of the binary file into
 * this memory.
 *
 * @param mem      The memory.
 * @param filename The path to the binary file.
 */
u8 *mem_load(cstr filename);
