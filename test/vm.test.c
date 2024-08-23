#include "../src/mem.h"
#include "../src/vm.h"
#include "utils/mu.h"
#include <stdlib.h>

extern Vm vm;

mu_unit({
  
  test("Run /files/add.vm", {
    uint8_t *code = mem_load("./test/files/add.vm");

    assert_int_equal(vm.ip, code);
    assert_int_equal(vm.dp, vm.dat);

    vm_run(code);

    assert_int_equal(vm.ip, code + (1 + 8) + (1 + 8) + 1 + 1);
    assert_int_equal(vm.dp, vm.dat + 1);
    assert_int_equal(*(vm.dp - 1), 0x3579);

    free(code);
  });

  // test("Run /files/sub.vm", {
  //   uint8_t *code = mem_load("./test/files/sub.vm");

  //   assert_int_equal(vm.ip, 0);
  //   assert_int_equal(vm.dp, 1023);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0xff);
  //   assert_int_equal(code[1022], 0xff);
  //   assert_int_equal(vm.ip, 3);
  //   assert_int_equal(vm.dp, 1021);

  //   vm_step(vm);
  //   assert_int_equal(code[1021], 0x00);
  //   assert_int_equal(code[1020], 0xff);
  //   assert_int_equal(vm.ip, 6);
  //   assert_int_equal(vm.dp, 1019);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0xff);
  //   assert_int_equal(code[1022], 0x00);
  //   assert_int_equal(vm.ip, 7);
  //   assert_int_equal(vm.dp, 1021);

  //   free(code);
  // });

  // test("Run /files/memop.vm", {
  //   uint8_t *code = mem_load("./test/files/memop.vm");

  //   assert_int_equal(vm.ip, 0);
  //   assert_int_equal(vm.dp, 1023);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x66);
  //   assert_int_equal(code[1022], 0x77);
  //   assert_int_equal(vm.ip, 3);
  //   assert_int_equal(vm.dp, 1021);

  //   // 1000 = 0x03e8
  //   vm_step(vm);
  //   assert_int_equal(code[1021], 0x03);
  //   assert_int_equal(code[1020], 0xe8);
  //   assert_int_equal(vm.ip, 6);
  //   assert_int_equal(vm.dp, 1019);

  //   // 1000 = 0x03e8
  //   vm_step(vm);
  //   assert_int_equal(code[1000], 0x66);
  //   assert_int_equal(code[1001], 0x77);
  //   assert_int_equal(vm.ip, 7);
  //   assert_int_equal(vm.dp, 1023);

  //   // 1000 = 0x03e8
  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x03);
  //   assert_int_equal(code[1022], 0xe8);
  //   assert_int_equal(vm.ip, 10);
  //   assert_int_equal(vm.dp, 1021);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x66);
  //   assert_int_equal(code[1022], 0x77);
  //   assert_int_equal(vm.ip, 11);
  //   assert_int_equal(vm.dp, 1021);

  //   free(code);
  // });

  // test("Run /files/mul.vm", {
  //   uint8_t *code = mem_load("./test/files/mul.vm");

  //   assert_int_equal(vm.ip, 0);
  //   assert_int_equal(vm.dp, 1023);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x00);
  //   assert_int_equal(code[1022], 0x03);
  //   assert_int_equal(vm.ip, 3);
  //   assert_int_equal(vm.dp, 1021);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x00);
  //   assert_int_equal(code[1022], 0x03);
  //   assert_int_equal(code[1021], 0x00);
  //   assert_int_equal(code[1020], 0x03);
  //   assert_int_equal(vm.ip, 4);
  //   assert_int_equal(vm.dp, 1019);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x00);
  //   assert_int_equal(code[1022], 0x09);
  //   assert_int_equal(vm.ip, 5);
  //   assert_int_equal(vm.dp, 1021);

  //   vm_step(vm);
  //   assert_int_equal(code[1021], 0x00);
  //   assert_int_equal(code[1020], 0x04);
  //   assert_int_equal(vm.ip, 8);
  //   assert_int_equal(vm.dp, 1019);

  //   vm_step(vm);
  //   assert_int_equal(code[1023], 0x00);
  //   assert_int_equal(code[1022], 0x02);
  //   assert_int_equal(vm.ip, 9);
  //   assert_int_equal(vm.dp, 1021);

  //   free(code);
  // });
})
