#include "../src/vm.h"
#include "utils/mu.h"
#include <stdint.h>

#define ARG(val)                   \
  (u8)(((u64)(val) >> 56) & 0xff), \
  (u8)(((u64)(val) >> 48) & 0xff), \
  (u8)(((u64)(val) >> 40) & 0xff), \
  (u8)(((u64)(val) >> 32) & 0xff), \
  (u8)(((u64)(val) >> 24) & 0xff), \
  (u8)(((u64)(val) >> 16) & 0xff), \
  (u8)(((u64)(val) >>  8) & 0xff), \
  (u8)(((u64)(val)      ) & 0xff)

u8 code1[] = { OP_PSH, ARG( 1), OP_PSH, ARG( 2), OP_ADD, OP_HLT };
u8 code2[] = { OP_PSH, ARG( 1), OP_PSH, ARG(-1), OP_ADD, OP_HLT };

mu_unit({
 
  test("ADD: 1 + 2", {
    vm_run(code1);
    assert_pointers_equal(vm.ip, code1 + 20);
    assert_pointers_equal(vm.dp, vm.dat + 1);
    assert_unsigned_equal(*(vm.dp - 1), 3);
  });

  test("ADD: 1 + (-1)", {
    vm_run(code2);
    assert_pointers_equal(vm.ip, code2 + 20);
    assert_pointers_equal(vm.dp, vm.dat + 1);
    assert_unsigned_equal(*(vm.dp - 1), 0);
  });

})
