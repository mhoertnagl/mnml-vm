#include <stdlib.h>
#include "vm.h"
#include "dev/dev.h"

u8 vm_pop8(Vm *vm)
{
  return vm->mem[--vm->sp];
}

u16 vm_pop(Vm *vm)
{
  const u8 h = vm->mem[--vm->sp];
  const u8 l = vm->mem[--vm->sp];
  return (h << 8) | l;
}

void vm_psh(Vm *vm, u16 v)
{
  vm->mem[vm->sp] = (v >> 8);
  vm->mem[vm->sp + 1] = v;
  vm->sp += 2;
}

u16 vm_ldw(Vm *vm, i16 a)
{
  const u8 h = vm->mem[vm->pc + a];
  const u8 l = vm->mem[vm->pc + a + 1];
  return (h << 8) | l;
}

void vm_stw(Vm *vm, i16 a, u16 v)
{
  vm->mem[vm->pc + a] = (v >> 8);
  vm->mem[vm->pc + a + 1] = v;
}

void vm_boot(Vm *vm, u8 *mem)
{
  vm->pc = 0;
  vm->sp = 0xffff; // TODO: Memory struct with size.
  vm->mem = mem;
  // for (int i = 0; i < DEV_MAX_ADDR; i++)
  // {
  //   vm->dev[i] = nul;
  // }
}

void vm_attach_device(Vm *vm, u8 addr, Device *dev)
{
  // TODO: Error handling.
  // if (addr > DEV_MAX_ADDR)
  // {
  //   return;
  // }
  // if (dev == NULL)
  // {
  //   return;
  // }
  vm->dev[addr] = dev;
}

// void vm_run(Vm *vm)
// {
//   while (1)
//   {
//     vm_step(vm);
//   }
// }

void vm_step(Vm *vm)
{
  switch (vm->mem[vm->pc])
  {
  case VM_PSH:
  {
    const u16 v = vm_ldw(vm, 1);
    vm_psh(vm, v);
    vm->pc += 3;
    break;
  }

  case VM_POP:
  {
    vm->sp++;
    vm->pc++;
    break;
  }

  case VM_NIP:
  {
    const u16 a = vm_pop(vm);
    vm_pop(vm);
    vm_psh(vm, a);

    // Alternative 1:
    // vm->sp--;
    // vm->mem[vm->sp - 1] = vm->mem[vm->sp];

    // Alternative 2 (??):
    // vm->mem[vm->sp - 1] = vm->mem[--vm->sp];

    vm->pc++;
    break;
  }

  case VM_SWP:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, a);
    vm_psh(vm, b);

    // Alternative 1:
    // const u16 t = vm->mem[vm->sp - 1];
    // vm->mem[vm->sp - 1] = vm->mem[vm->sp - 2];
    // vm->mem[vm->sp - 2] = t;

    // Alternative 2:
    // vm->mem[vm->sp - 1] ^= vm->mem[vm->sp - 2];
    // vm->mem[vm->sp - 2] ^= vm->mem[vm->sp - 1];
    // vm->mem[vm->sp - 1] ^= vm->mem[vm->sp - 2];

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

    // Alternative 1:
    // vm->mem[vm->sp] = vm->mem[vm->sp - 2];
    // vm->sp++;

    vm->pc++;
    break;
  }

  case VM_DUP:
  {
    const u16 a = vm_pop(vm);
    vm_psh(vm, a);
    vm_psh(vm, a);

    // Alternative 1:
    // vm->mem[vm->sp] = vm->mem[vm->sp - 1];
    // vm->sp++;

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

  case VM_INC:
  {
    const u16 a = vm_pop(vm);
    vm_psh(vm, a + 1);
    vm->pc++;
    break;
  }

  case VM_DEC:
  {
    const u16 a = vm_pop(vm);
    vm_psh(vm, a - 1);
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

  case VM_XOR:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b ^ a);
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

  case VM_NEQ:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b != a);
    // vm_psh(vm, b != a ? 1 : 0);
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

  case VM_SGT:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b > a);
    // vm_psh(vm, b > a ? 1 : 0);
    vm->pc++;
    break;
  }

  case VM_SLE:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b <= a);
    // vm_psh(vm, b <= a ? 1 : 0);
    vm->pc++;
    break;
  }

  case VM_SGE:
  {
    const u16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm_psh(vm, b >= a);
    // vm_psh(vm, b >= a ? 1 : 0);
    vm->pc++;
    break;
  }

  case VM_JMP:
  {
    const i16 a = vm_pop(vm);
    vm->pc += a;
    break;
  }

  case VM_JAL:
  {
    const i16 a = vm_pop(vm);
    vm_psh(vm, vm->pc + 1);
    vm->pc += a;
    break;
  }

  case VM_BRA:
  {
    const i16 a = vm_pop(vm);
    const u16 b = vm_pop(vm);
    vm->pc += b ? a : 1;
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
    const u8 a = vm_pop8(vm);
    const u16 r = vm_pop(vm);
    const Device *dev = vm->dev[a];
    const u16 v = dev->read(dev->state, r);
    vm_psh(vm, v);
    break;
  }

  case VM_DTX:
  {
    const u8 a = vm_pop8(vm);
    const u16 r = vm_pop(vm);
    const u16 v = vm_pop(vm);
    const Device *dev = vm->dev[a];
    dev->write(dev->state, r, v);
    break;
  }

  default:
    break;
  }
}
