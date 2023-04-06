#include "utils/mu.h"
#include "../src/vm/vm.h"
#include "../src/mem/mem.h"

mu_unit({
  test("Initialize memory with /files/01.as", {
    Mem *mem = new_mem(1000);
    mem_init(mem, "./test/files/01.vm");
    assert_int_equal(mem->dat[0], VM_PSH);
    assert_int_equal(mem->dat[1], VM_POP);
    assert_int_equal(mem->dat[2], VM_NIP);
    assert_int_equal(mem->dat[3], VM_SWP);
    assert_int_equal(mem->dat[4], VM_OVR);
    assert_int_equal(mem->dat[5], VM_DUP);
    assert_int_equal(mem->dat[6], VM_ROT);
    assert_int_equal(mem->dat[7], VM_INC);
    assert_int_equal(mem->dat[8], VM_DEC);
    assert_int_equal(mem->dat[9], VM_ADD);
    assert_int_equal(mem->dat[10], VM_SUB);
    assert_int_equal(mem->dat[11], VM_MUL);
    assert_int_equal(mem->dat[12], VM_DIV);
    assert_int_equal(mem->dat[13], VM_NOT);
    assert_int_equal(mem->dat[14], VM_AND);
    assert_int_equal(mem->dat[15], VM_OOR);
    assert_int_equal(mem->dat[16], VM_XOR);
    assert_int_equal(mem->dat[17], VM_SLL);
    assert_int_equal(mem->dat[18], VM_SRL);
    assert_int_equal(mem->dat[19], VM_EQU);
    assert_int_equal(mem->dat[20], VM_NEQ);
    assert_int_equal(mem->dat[21], VM_SLT);
    assert_int_equal(mem->dat[22], VM_SGT);
    assert_int_equal(mem->dat[23], VM_SLE);
    assert_int_equal(mem->dat[24], VM_SGE);
    assert_int_equal(mem->dat[25], VM_JMP);
    assert_int_equal(mem->dat[26], VM_JAL);
    assert_int_equal(mem->dat[27], VM_BRA);
    assert_int_equal(mem->dat[28], VM_LDW);
    assert_int_equal(mem->dat[29], VM_STW);
    assert_int_equal(mem->dat[30], VM_DRX);
    assert_int_equal(mem->dat[31], VM_DTX);
    assert_int_equal(mem->dat[32], 0);
    free_mem(mem);
  });
})
