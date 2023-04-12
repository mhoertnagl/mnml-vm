#include "utils/mu.h"
#include "../src/vm/vm.h"
#include "../src/mem/mem.h"

mu_unit({
  test("Run /files/02.vm", {
    Mem *mem = new_mem(1024);
    Vm *vm = new_vm();
    mem_init(mem, "./test/files/02.vm");
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
})
