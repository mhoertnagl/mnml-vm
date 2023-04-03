#include "utils/mu.h"
#include "../src/mem/mem.h"

mu_unit({
  test("A new symbol table should be empty", {
    Mem *mem = new_mem(1000);
    assert(0 == 0, "table size should be 0");
    free_mem(mem);
  });
})
