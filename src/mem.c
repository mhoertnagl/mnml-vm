#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

u8 *mem_load(cstr filename) {
  FILE *img = fopen(filename, "rb");

  if (img == NULL) {
    fprintf(stderr, "ERROR: Could not open file [%s].\n", filename);
    exit(EXIT_FAILURE);
  }
  fseek(img, 0, SEEK_END);
  long len = ftell(img);
  u8 *code = calloc(len, sizeof(u8));
  rewind(img);
  fread(code, len, sizeof(u8), img);
  fclose(img);
  return code;
}
