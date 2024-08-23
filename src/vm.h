#pragma once

#include <inttypes.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint64_t u64;

#define MEMORY_SIZE       65536
#define DATA_STACK_SIZE     512
#define RETURN_STACK_SIZE   256

typedef enum {
  VM_SUCCESS,
  VM_ERROR_UNKNOWN_OPCODE
} VmResult;

typedef enum {
  OP_PSH,
  OP_DUP,
  // OP_LDI,
  // OP_STI,
  OP_LDW,
  OP_STW,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  // OP_AND,
  // OP_OOR,
  // OP_NOT,
  // OP_SLL,
  // OP_SRL,
  OP_EQU,
  OP_NEQ,
  OP_SGT,
  OP_SGE,
  OP_SLT,
  OP_SLE,
  OP_JMP,
  OP_BRA,
  // OP_BEQ,
  // OP_BNE,
  OP_JAL,
  OP_RET,
  OP_HLT  // Halt the VM.
} OpCode;

typedef struct {
  // Instruction pointer.
  u8 *ip;
  // Fixed-size data stack.
  u64 dat[DATA_STACK_SIZE];
  u64 *dp;
  // Fixed-size return stack.
  u8 *ret[RETURN_STACK_SIZE];
  u8 **rp;
  // Fixed-size memory.
  u64 mem[MEMORY_SIZE];
} Vm;

VmResult vm_run(u8 *code);
