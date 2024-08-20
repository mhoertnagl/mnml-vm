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

#define POP() \
  ((vm->mem[++vm->sp] << 8) | vm->mem[++vm->sp])

#define PUSH(v)              \
  vm->mem[vm->sp--] = v;     \
  vm->mem[vm->sp--] = v >> 8 

#define RET_POP() \
  ((vm->mem[++vm->rp] << 8) | vm->mem[++vm->rp])

#define RET_PUSH(v)          \
  vm->mem[vm->rp--] = v;     \
  vm->mem[vm->rp--] = v >> 8 

#define LOAD_WORD(a) \
  ((vm->mem[a] << 8) | vm->mem[a + 1])

#define STORE_WORD(a, v) \
  vm->mem[a] = v >> 8;   \
  vm->mem[a + 1] = v

#define UNARY_OP(op)      \
  const u16 b = op POP(); \
  PUSH(b);                \
  vm->pc++;

#define BINARY_OP(op)   \
  const u16 a = POP();  \
  const u16 b = POP();  \
  const u16 c = b op a; \
  PUSH(c);              \
  vm->pc++;

void vm_step(Vm *vm)
{
  // clang-format off
  switch (vm->mem[vm->pc])
  {
  case VM_PSH:
  {
    vm->pc++;
    const u16 v = LOAD_WORD(vm->pc);
    PUSH(v);
    vm->pc += 2;
    break;
  }
  case VM_POP: { vm->sp += 2; vm->pc++; break; }
  case VM_DUP:
  {
    // Is this correct?
    const u8 l = vm->mem[vm->sp + 1];
    const u8 h = vm->mem[vm->sp + 2];
    const u16 a = (h << 8) | l;
    PUSH(a);
    vm->pc++;
    break;
  }
  case VM_SWP:
  {
    const u16 a = POP();
    const u16 b = POP();
    PUSH(a);
    PUSH(b);
    vm->pc++;
    break;
  }
  case VM_ROT:
  {
    const u16 a = POP();
    const u16 b = POP();
    const u16 c = POP();
    PUSH(a);
    PUSH(c);
    PUSH(b);
    vm->pc++;
    break;
  }
  case VM_OVR:
  {
    const u16 a = POP();
    const u16 b = POP();
    PUSH(b);
    PUSH(a);
    PUSH(b);
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
  case VM_JMP: { vm->pc = POP(); break; }
  case VM_JAL:
  {
    const u16 pc = vm->pc;
    vm->pc = POP();
    const u16 pc1 = pc + 1;
    RET_PUSH(pc1);
    break;
  }
  case VM_BRA:
  {
    const i16 a = POP();
    const u16 b = POP();
    vm->pc += b ? a : 1;
    break;
  }
  case VM_RET: { vm->pc = RET_POP(); break; }
  case VM_LDR:
  {
    const u16 a = RET_POP();
    PUSH(a);
    vm->pc++;
    break;
  }
  case VM_STR:
  {
    const u16 a = POP();
    RET_PUSH(a);
    vm->pc++;
    break;
  }
  case VM_LDW:
  {
    const u16 a = POP();
    const u16 v = LOAD_WORD(a);
    PUSH(v);
    vm->pc++;
    break;
  }
  case VM_STW:
  {
    const u16 a = POP();
    const u16 v = POP();
    STORE_WORD(a, v);
    vm->pc++;
    break;
  }
  case VM_DRX:
  {
    const u16 a = POP();
    const u16 r = POP();
    const u16 v = dev_read(vm->dev[a], r);
    PUSH(v);
    vm->pc++;
    break;
  }
  case VM_DTX:
  {
    const u16 a = POP();
    const u16 r = POP();
    const u16 v = POP();
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
