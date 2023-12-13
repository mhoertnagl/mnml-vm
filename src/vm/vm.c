#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

u16 vm_pop(Vm *vm)
{
  const u8 l = vm->mem[++vm->sp];
  const u8 h = vm->mem[++vm->sp];
  return (h << 8) | l;
}

void vm_psh(Vm *vm, u16 v)
{
  vm->mem[vm->sp--] = (v >> 8) & 0xff;
  vm->mem[vm->sp--] = v & 0xff;
}

u16 vm_rs_pop(Vm *vm)
{
  const u8 l = vm->mem[++vm->rp];
  const u8 h = vm->mem[++vm->rp];
  return (h << 8) | l;
}

void vm_rs_psh(Vm *vm, u16 v)
{
  vm->mem[vm->rp--] = (v >> 8) & 0xff;
  vm->mem[vm->rp--] = v & 0xff;
}

u16 vm_ldw(Vm *vm, u16 a)
{
  const u8 h = vm->mem[a];
  const u8 l = vm->mem[a + 1];
  return (h << 8) | l;
}

void vm_stw(Vm *vm, u16 a, u16 v)
{
  vm->mem[a] = (v >> 8) & 0xff;
  vm->mem[a + 1] = v & 0xff;
}

Vm *new_vm()
{
  Vm *vm = malloc(sizeof(Vm));
  vm->pc = 0;
  vm->sp = 0;
  vm->rp = 0;
  return vm;
}

void free_vm(Vm *vm)
{
  free(vm);
}

void vm_attach_memory(Vm *vm, Mem *mem)
{
  vm->mem = mem->dat;
  vm->pc = 0;
  // Data stack starts before the return stack.
  vm->sp = mem->len - RETURN_STACK_SIZE - 1;
  // Return stack starts at the end of the memory.
  vm->rp = mem->len - 1;
}

void vm_attach_device(Vm *vm, u8 addr, Device *dev)
{
  vm->dev[addr] = dev;
}

void vm_step(Vm *vm)
{
  switch (vm->mem[vm->pc])
  {
  case VM_PSH:
  {
    const u16 v = vm_ldw(vm, ++vm->pc);
    vm_psh(vm, v);
    vm->pc += 2;
    break;
  }
  case VM_POP:
  {
    vm_pop(vm);
    vm->pc++;
    break;
  }
  case VM_DUP:
  {
    const u16 a = vm_pop(vm);
    vm_psh(vm, a);
    vm_psh(vm, a);
    vm->pc++;
    break;
  }
  case VM_SWP:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, a);
    vm_psh(vm, b);
    vm->pc++;
    break;
  }
  case VM_ROT:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    const u16 c = vm_pop(vm);
    vm_psh(vm, a);
    vm_psh(vm, c);
    vm_psh(vm, b);
    vm->pc++;
    break;
  }
  case VM_OVR:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b);
    vm_psh(vm, a);
    vm_psh(vm, b);
    vm->pc++;
    break;
  }
  case VM_ADD:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b + a);
    vm->pc++;
    break;
  }
  case VM_SUB:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b - a);
    vm->pc++;
    break;
  }
  case VM_MUL:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b * a);
    vm->pc++;
    break;
  }
  case VM_DIV:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b / a);
    vm->pc++;
    break;
  }
  case VM_NOT:
  {
    const u16 a = vm_pop(vm);
    // vm_psh(vm, a ? 0 : 1);
    vm_psh(vm, !a);
    vm->pc++;
    break;
  }
  case VM_AND:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b & a);
    vm->pc++;
    break;
  }
  case VM_OOR:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b | a);
    vm->pc++;
    break;
  }
  case VM_SLL:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b << a);
    vm->pc++;
    break;
  }
  case VM_SRL:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b >> a);
    vm->pc++;
    break;
  }
  case VM_EQU:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b == a);
    // vm_psh(vm, b == a ? 1 : 0);
    vm->pc++;
    break;
  }
  case VM_SLT:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b < a);
    // vm_psh(vm, b < a ? 1 : 0);
    vm->pc++;
    break;
  }
  case VM_JMP:
  {
    vm->pc = vm_pop(vm);
    break;
  }
  case VM_JAL:
  {
    const u16 pc = vm->pc;
    vm->pc = vm_pop(vm);
    vm_rs_psh(vm, pc + 1);
    break;
  }
  case VM_BRA:
  {
    const i16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
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
    vm_psh(vm, vm_rs_pop(vm));
    vm->pc++;
    break;
  }
  case VM_STR:
  {
    vm_rs_psh(vm, vm_pop(vm));
    vm->pc++;
    break;
  }
  case VM_LDW:
  {
    const u16 a = vm_pop(vm);
    const u16 v = vm_ldw(vm, a);
    vm_psh(vm, v);
    vm->pc++;
    break;
  }
  case VM_STW:
  {
    const u16 a = vm_pop(vm);
    const u16 v = vm_pop(vm);
    vm_stw(vm, a, v);
    vm->pc++;
    break;
  }
  case VM_DRX:
  {
    const u16 a = vm_pop(vm);
    const u16 r = vm_pop(vm);
    const u16 v = dev_read(vm->dev[a], r);
    vm_psh(vm, v);
    vm->pc++;
    break;
  }
  case VM_DTX:
  {
    const u16 a = vm_pop(vm);
    const u16 r = vm_pop(vm);
    const u16 v = vm_pop(vm);
    dev_write(vm->dev[a], r, v);
    vm->pc++;
    break;
  }
  default:
    printf("ERROR: Unsupported operation [%x].\n", vm->mem[vm->pc]);
    vm->pc++;
    break;
  }
}
