#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

Vm *vm_new()
{
  Vm *vm = malloc(sizeof(Vm));
  vm->pc = 0;
  vm->sp = 0;
  vm->rp = 0;
  return vm;
}

void vm_free(Vm *vm)
{
  free(vm);
}

void vm_attach_memory(Vm *vm, Mem *mem)
{
  vm->mem = mem->dat;
  vm->pc = 0;
  // Return stack starts at the end of the memory.
  vm->rp = mem->len - 1;
  // Data stack starts before the return stack.
  vm->sp = vm->rp - RETURN_STACK_SIZE;
}

void vm_attach_device(Vm *vm, u8 addr, Device *dev)
{
  vm->dev[addr] = dev;
}

// TODO: This would give a stack like
// @00 0x12
// @01 0x34
// @02 ----
// -> pop would give 0x1234
#define POP(var) \
  ((vm->mem[++vm->sp] << 8) | vm->mem[++vm->sp])

#define POP(var)                          \
  const u8 l##var = vm->mem[++vm->sp];    \
  const u8 h##var = vm->mem[++vm->sp];    \
  const u16 var = (h##var << 8) | l##var;

#define POP_SIGNED(var)                   \
  const u8 l##var = vm->mem[++vm->sp];    \
  const u8 h##var = vm->mem[++vm->sp];    \
  const i16 var = (h##var << 8) | l##var;

#define PUSH(v)                          \
  vm->mem[vm->sp--] = ((v) >> 8) & 0xff; \
  vm->mem[vm->sp--] = (v) & 0xff;

static u16 vm_rs_pop(Vm *vm)
{
  const u8 l = vm->mem[++vm->rp];
  const u8 h = vm->mem[++vm->rp];
  return (h << 8) | l;
}

static void vm_rs_psh(Vm *vm, u16 v)
{
  vm->mem[vm->rp--] = (v >> 8) & 0xff;
  vm->mem[vm->rp--] = v & 0xff;
}

#define LOAD_WORD(a) \
  ((vm->mem[a] << 8) | vm->mem[a + 1])

// #define LOAD_WORD(a) ((u16 *)vm->mem)[a]

#define STORE_WORD(a, v)        \
  vm->mem[a] = (v >> 8) & 0xff; \
  vm->mem[a + 1] = v & 0xff;

#define UNARY_OP(op)  \
  POP(a)              \
  const u16 b = op a; \
  PUSH(b)             \
  vm->pc++;

#define BINARY_OP(op)   \
  POP(a)                \
  POP(b)                \
  const u16 c = b op a; \
  PUSH(c)               \
  vm->pc++;

void vm_step(Vm *vm)
{
  // clang-format off
  switch (vm->mem[vm->pc])
  {
  case VM_PSH:
  {
    vm->pc++;
    u16 v = LOAD_WORD(vm->pc);
    PUSH(v)
    vm->pc += 2;
    break;
  }
  case VM_POP:
  {
    vm->sp += 2;
    vm->pc++;
    break;
  }
  case VM_DUP:
  {
    // Is this correct?
    const u8 l = vm->mem[vm->sp + 1];
    const u8 h = vm->mem[vm->sp + 2];
    u16 a = (h << 8) | l;
    PUSH(a)
    vm->pc++;
    break;
  }
  case VM_SWP:
  {
    POP(a)
    POP(b)
    PUSH(a)
    PUSH(b)
    vm->pc++;
    break;
  }
  case VM_ROT:
  {
    POP(a)
    POP(b)
    POP(c)
    PUSH(a)
    PUSH(c)
    PUSH(b)
    vm->pc++;
    break;
  }
  case VM_OVR:
  {
    POP(a)
    POP(b)
    PUSH(b)
    PUSH(a)
    PUSH(b)
    vm->pc++;
    break;
  }
  case VM_ADD: { BINARY_OP(+)  break; }
  case VM_SUB: { BINARY_OP(-)  break; }
  case VM_MUL: { BINARY_OP(*)  break; }
  case VM_DIV: { BINARY_OP(/)  break; }
  case VM_NOT: { UNARY_OP(!)   break; }
  case VM_AND: { BINARY_OP(&)  break; }
  case VM_OOR: { BINARY_OP(|)  break; }
  case VM_SLL: { BINARY_OP(<<) break; }
  case VM_SRL: { BINARY_OP(>>) break; }
  case VM_EQU: { BINARY_OP(==) break; }
  case VM_SLT: { BINARY_OP(<)  break; }
  case VM_JMP: 
  {
    POP(a)
    vm->pc = a;
    break;
  }
  case VM_JAL:
  {
    const u16 pc = vm->pc;
    POP(a)
    vm->pc = a;
    vm_rs_psh(vm, pc + 1);
    break;
  }
  case VM_BRA:
  {
    POP_SIGNED(a)
    POP(b)
    vm->pc += b ? a : 1;
    break;
  }
  case VM_RET:
  {
    vm->pc = vm_rs_pop(vm);
    break;
  }
  case VM_LDR:
  {
    u16 a = vm_rs_pop(vm);
    PUSH(a)
    vm->pc++;
    break;
  }
  case VM_STR:
  {
    POP(a)
    vm_rs_psh(vm, a);
    vm->pc++;
    break;
  }
  case VM_LDW:
  {
    POP(a)
    u16 v = LOAD_WORD(a);
    PUSH(v)
    vm->pc++;
    break;
  }
  case VM_STW:
  {
    POP(a)
    POP(v)
    STORE_WORD(a, v)
    vm->pc++;
    break;
  }
  case VM_DRX:
  {
    POP(a)
    POP(r)
    const u16 v = dev_read(vm->dev[a], r);
    PUSH(v)
    vm->pc++;
    break;
  }
  case VM_DTX:
  {
    POP(a)
    POP(r)
    POP(v)
    dev_write(vm->dev[a], r, v);
    vm->pc++;
    break;
  }
  default:
    printf("ERROR: Unsupported operation [%x].\n", vm->mem[vm->pc]);
    vm->pc++;
    break;
  }
  // clang-format on
}
