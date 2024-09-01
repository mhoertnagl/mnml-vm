#pragma once

#include <inttypes.h>
#include <stdint.h>

typedef uint8_t  u8;
typedef uint64_t u64;

// #define MEMORY_SIZE     65536
#define DATA_STACK_SIZE 1024
#define CALL_STACK_SIZE 1024

typedef enum {
  VM_SUCCESS,
  VM_ERROR_UNKNOWN_OPCODE
} VmResult;

typedef enum {
  OP_PSH,
  // OP_POP,
  // OP_DUP,
  // OP_LDI,
  // OP_STI,
  // OP_LDW,
  // OP_STW,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  // OP_AND,
  // OP_OR,
  // OP_NOT,
  // OP_SLL,
  // OP_SRL,
  OP_EQ,
  OP_NE,
  OP_GT,
  OP_GE,
  OP_LT,
  OP_LE,
  OP_JMP,
  OP_JEZ,
  // OP_JEQ,
  OP_CALL,
  OP_RET,
  OP_PSHV,
  OP_LDV,
  OP_STV,
  OP_HLT  // Halt the VM.
} OpCode;

typedef struct {
  // Instruction pointer.
  u8 *ip;
  // Fixed-size data stack.
  u64 dat[DATA_STACK_SIZE];
  u64 *dp;
  // Fixed-size call stack.
  u64 cal[CALL_STACK_SIZE];
  u64 *cp;
  u64 *fp;
  // Fixed-size memory.
  // u64 mem[MEMORY_SIZE];
} Vm;

extern Vm vm;

VmResult vm_run(u8 *code);
