#include "utils/mu.h"
#include "../src/vm/vm.h"
#include "../src/mem/mem.h"

mu_unit({
  test("Run /files/add.vm", {
    Mem *mem = new_mem(1024);
    Vm *vm = new_vm();
    mem_init(mem, "./test/files/add.vm");
    vm_attach_memory(vm, mem);

    assert_int_equal(vm->pc, 0);
    assert_int_equal(vm->sp, 1023);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0x12);
    assert_int_equal(mem->dat[1022], 0x34);
    assert_int_equal(vm->pc, 3);
    assert_int_equal(vm->sp, 1021);

    vm_step(vm);
    assert_int_equal(mem->dat[1021], 0x23);
    assert_int_equal(mem->dat[1020], 0x45);
    assert_int_equal(vm->pc, 6);
    assert_int_equal(vm->sp, 1019);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0x35);
    assert_int_equal(mem->dat[1022], 0x79);
    assert_int_equal(vm->pc, 7);
    assert_int_equal(vm->sp, 1021);

    free_vm(vm);
    free_mem(mem);
  });

  test("Run /files/sub.vm", {
    Mem *mem = new_mem(1024);
    Vm *vm = new_vm();
    mem_init(mem, "./test/files/sub.vm");
    vm_attach_memory(vm, mem);

    assert_int_equal(vm->pc, 0);
    assert_int_equal(vm->sp, 1023);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0xff);
    assert_int_equal(mem->dat[1022], 0xff);
    assert_int_equal(vm->pc, 3);
    assert_int_equal(vm->sp, 1021);

    vm_step(vm);
    assert_int_equal(mem->dat[1021], 0x00);
    assert_int_equal(mem->dat[1020], 0xff);
    assert_int_equal(vm->pc, 6);
    assert_int_equal(vm->sp, 1019);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0xff);
    assert_int_equal(mem->dat[1022], 0x00);
    assert_int_equal(vm->pc, 7);
    assert_int_equal(vm->sp, 1021);

    free_vm(vm);
    free_mem(mem);
  });

  test("Run /files/memop.vm", {
    Mem *mem = new_mem(1024);
    Vm *vm = new_vm();
    mem_init(mem, "./test/files/memop.vm");
    vm_attach_memory(vm, mem);

    assert_int_equal(vm->pc, 0);
    assert_int_equal(vm->sp, 1023);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0x66);
    assert_int_equal(mem->dat[1022], 0x77);
    assert_int_equal(vm->pc, 3);
    assert_int_equal(vm->sp, 1021);

    // 1000 = 0x03e8
    vm_step(vm);
    assert_int_equal(mem->dat[1021], 0x03);
    assert_int_equal(mem->dat[1020], 0xe8);
    assert_int_equal(vm->pc, 6);
    assert_int_equal(vm->sp, 1019);

    // 1000 = 0x03e8
    vm_step(vm);
    assert_int_equal(mem->dat[1000], 0x66);
    assert_int_equal(mem->dat[1001], 0x77);
    assert_int_equal(vm->pc, 7);
    assert_int_equal(vm->sp, 1023);

    // 1000 = 0x03e8
    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0x03);
    assert_int_equal(mem->dat[1022], 0xe8);
    assert_int_equal(vm->pc, 10);
    assert_int_equal(vm->sp, 1021);

    vm_step(vm);
    assert_int_equal(mem->dat[1023], 0x66);
    assert_int_equal(mem->dat[1022], 0x77);
    assert_int_equal(vm->pc, 11);
    assert_int_equal(vm->sp, 1021);

    free_vm(vm);
    free_mem(mem);
  });
})
