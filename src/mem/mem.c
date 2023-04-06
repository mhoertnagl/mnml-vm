#include <stdio.h>
#include <stdlib.h>
#include "mem/mem.h"
#include "utils/errio.h"

// clang-format off
#define MEM_EXCEED "WARN: File size [%d bytes] exceeds memory size [%d bytes].\n"
#define NOT_FOUND  "ERROR: Could not open file [%s].\n"
// clang-format on

Mem *new_mem(u32 size)
{
  Mem *mem = malloc(sizeof(Mem));
  mem->dat = calloc(size, sizeof(u8));
  mem->len = size;
  return mem;
}

void free_mem(Mem *mem)
{
  free(mem->dat);
  free(mem);
}

void mem_init(Mem *mem, cstr filename)
{
  FILE *img = fopen(filename, "rb");

  if (img == NULL)
  {
    perrorf(NOT_FOUND, filename);
  }

  fseek(img, 0, SEEK_END);
  u32 len = ftell(img);
  if (len > mem->len)
  {
    perrorf(MEM_EXCEED, len, mem->len);
    fclose(img);
    return;
  }

  rewind(img);
  fread(mem->dat, len, sizeof(u8), img);
  fclose(img);
}
