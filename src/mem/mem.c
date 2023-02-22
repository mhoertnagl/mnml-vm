#include <stdio.h>
#include <stdlib.h>
#include "mem/mem.h"

cstr MEM_EXCEED = "WARN: File size [%d bytes] exceeds memory size [%d bytes].";

Mem *mem_create(u32 size)
{
  Mem *mem = malloc(sizeof(Mem));
  mem->dat = calloc(size, sizeof(u8));
  mem->len = size;
  return mem;
}

void mem_init(Mem *mem, cstr filename)
{
  FILE *fptr = fopen(filename, "rb");
  fseek(fptr, 0, SEEK_END);
  u32 len = ftell(fptr);

  if (len < mem->len)
  {
    printf(MEM_EXCEED, len, mem->len);
    fclose(fptr);
    return;
  }

  rewind(fptr);
  fread(mem, len, sizeof(u8), fptr);
  fclose(fptr);
}

void mem_destroy(Mem *mem)
{
  free(mem->dat);
  free(mem);
}