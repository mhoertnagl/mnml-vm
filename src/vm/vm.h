#ifndef VM_H
#define VM_H

#include "dev/dev.h"

#define DEV_MAX_ADDR 15

// #define VM_LIT 0x00

#define VM_PSH 0x01 // ( -- a) a is the next 2 bytes of the binary.
#define VM_POP 0x02 // (a -- )
#define VM_NIP 0x03 // (a b -- a)
#define VM_SWP 0x04 // (a b -- b a)
#define VM_OVR 0x05 // (a b -- b a b) -+- Special cases of DUP.n where 1 <= n <= 15 from the lower 4 bits of the instruction.
#define VM_DUP 0x06 // (a -- a a) -----+
#define VM_ROT 0x07 // (a b c -- b c a)

// #define VM_INC 0x00 // (a -- (a + 1))
// #define VM_DEC 0x00 // (a -- (a - 1))

#define VM_ADD 0x08 // (a b -- (b + a))
#define VM_SUB 0x09 // (a b -- (b - a))
#define VM_MUL 0x0a // (a b -- (b * a))
#define VM_DIV 0x0b // (a b -- (b / a)) Integer division.
// #define VM_REM 0x00 // (a b -- (b % a))

#define VM_NOT 0x0c // (a -- (!a))
#define VM_AND 0x0d // (a b -- (b & a))
#define VM_OOR 0x0e // (a b -- (b | a))
// #define VM_NOR 0x00 // (a b -- (!(b | a)))
#define VM_XOR 0x0f // (a b -- (b ^ a))
#define VM_SLL 0x10 // (a b -- (b << a))
#define VM_SRL 0x11 // (a b -- (b >> a))
// #define VM_SRA 0x00 // (a b -- (b >>> a))

#define VM_EQU 0x12 // (a b -- (b == a)) Equality pushes 1 else 0
#define VM_NEQ 0x13 // (a b -- (b != a))
#define VM_SLT 0x14 // (a b -- (b < a))
#define VM_SGT 0x15 // (a b -- (b > a))
// #define VM_SLE 0x00 // (a b -- (b <= a))
// #define VM_SGE 0x00 // (a b -- (b >= a))

#define VM_JMP 0x16 // (a -- ) pc += a
#define VM_JAL 0x17 // (a -- (pc+1) a) pc += a
#define VM_BRA 0x18 // (a b -- ) if b then pc += a

#define VM_LDW 0x19 // (a r -- dev[a]->mem[r])
#define VM_STW 0x1a // (a r b -- ) dev[a]->mem[r] = b

#define VM_DRX 0x1b // (a b -- dev[b].read(a)) --------+
#define VM_DTX 0x1c // (a b c -- ) dev[b].write(a, c) -+- Lower 4 bit could identify the device. This would allow for 15 devices in total.

// clang-format off
typedef struct Vm
{
  u16    pc;
  u16    sp;
  u8     *mem;
  Device *dev[DEV_MAX_ADDR];
} Vm;
// clang-format off

inline u8 vm_pop8(Vm *vm)
{
  return vm->mem[--vm->sp];
}

inline u16 vm_pop(Vm *vm)
{
  const u8 h = vm->mem[--vm->sp];
  const u8 l = vm->mem[--vm->sp];
  return (h << 8) | l;
}

inline void vm_psh(Vm *vm, u16 v)
{
  vm->mem[vm->sp] = (v >> 8);
  vm->mem[vm->sp + 1] = v;
  vm->sp += 2;
}

inline u16 vm_ldw(Vm *vm, i16 a)
{
  const u8 h = vm->mem[vm->pc + a];
  const u8 l = vm->mem[vm->pc + a + 1];
  return (h << 8) | l;
}

inline void vm_stw(Vm *vm, i16 a, u16 v)
{
  vm->mem[vm->pc + a] = (v >> 8);
  vm->mem[vm->pc + a + 1] = v;
}

#endif