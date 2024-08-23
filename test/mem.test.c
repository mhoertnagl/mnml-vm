#include "../src/mem.h"
#include "../src/vm.h"
#include "utils/mu.h"
#include <stdlib.h>

mu_unit({
  test("Initialize memory with /files/01.as", {
    uint8_t *code = mem_load("./test/files/01.vm");
    assert_int_equal(code[ 0], OP_PSH);
    assert_int_equal(code[ 1], OP_DUP);
    assert_int_equal(code[ 2], OP_LDW);
    assert_int_equal(code[ 3], OP_STW);
    assert_int_equal(code[ 4], OP_ADD);
    assert_int_equal(code[ 5], OP_SUB);
    assert_int_equal(code[ 6], OP_MUL);
    assert_int_equal(code[ 7], OP_DIV);
    assert_int_equal(code[ 8], OP_EQU);
    assert_int_equal(code[ 9], OP_NEQ);
    assert_int_equal(code[10], OP_SGT);
    assert_int_equal(code[11], OP_SGE);
    assert_int_equal(code[12], OP_SLT);
    assert_int_equal(code[13], OP_SLE);
    assert_int_equal(code[14], OP_JMP);
    assert_int_equal(code[15], OP_BRA);
    assert_int_equal(code[16], OP_JAL);
    assert_int_equal(code[17], OP_RET);
    assert_int_equal(code[18], OP_HLT);
    free(code);
  });
})
