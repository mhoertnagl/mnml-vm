#pragma once

#include "../mem/mem.h"
#include "../dev/dev.h"

/** Maximum device address. */
#define DEV_MAX_ADDR 15

/** Size of the return stack. */
#define RETURN_STACK_SIZE 128

// clang-format off
#define VM_PSH 0x00 // (       -- a              )
#define VM_POP 0x01 // ( a     --                )
#define VM_DUP 0x02 // ( a     -- a a            )
#define VM_SWP 0x03 // ( a b   -- b a            )
#define VM_ROT 0x04 // ( a b c -- b c a          )
#define VM_OVR 0x05 // ( a b   -- a b a          )
#define VM_ADD 0x06 // ( a b   -- b+a            )
#define VM_SUB 0x07 // ( a b   -- b-a            )
#define VM_MUL 0x08 // ( a b   -- b*a            )
#define VM_DIV 0x09 // ( a b   -- ⌊b/a⌋          )
#define VM_NOT 0x0a // ( a     -- !a             )
#define VM_AND 0x0b // ( a b   -- b&a            )
#define VM_OOR 0x0c // ( a b   -- b|a            )
#define VM_SLL 0x0d // ( a b   -- b<<a           )
#define VM_SRL 0x0e // ( a b   -- b>>a           )
#define VM_EQU 0x0f // ( a b   -- b==a?1:0       )
#define VM_SLT 0x10 // ( a b   -- b<a            )
#define VM_JMP 0x11 // ( a     --                ) pc = a
#define VM_JAL 0x12 // ( a     --                ) rs_push(pc); pc = a
#define VM_BRA 0x13 // ( a b   --                ) if b then pc = a
#define VM_RET 0x14
#define VM_LDR 0x15
#define VM_STR 0x16
#define VM_LDW 0x17 // ( a     -- mem[a]         )
#define VM_STW 0x18 // ( a v   --                ) mem[a] = v
#define VM_DRX 0x19 // ( a d   -- dev[d].read(a) )
#define VM_DTX 0x1a // ( a d v --                ) dev[d].write(a, v)

// SIDE EFFECTS
// ------------------------------------------
// VM_PSH - Pushes the next two bytes in the 
//          binary onto the stack.
// VM_JMP - Sets the program counter to the 
//          top of the stack.
// VM_JAL - Sets the program counter to the 
//          top of the stack.
// VM_BRA - Sets the program counter to the 
//          second element on the stack if
//          the top element evaluates to 1.
// VM_STW - Stores the second element in 
//          memory at the address specified
//          by the top element on the stack.
// VM_DTX - Writes the third element on the
//          stack to the memory address of 
//          the top element of the device 
//          identified by the second element.
// clang-format on

typedef struct
{
  // clang-format off
  u8     *mem;
  Device *dev[DEV_MAX_ADDR];
  u16    pc;
  u16    sp;
  u16    rp;
  // clang-format on
} Vm;

Vm *vm_new();

void vm_free(Vm *vm);

void vm_attach_memory(Vm *vm, Mem *mem);

void vm_attach_device(Vm *vm, u8 addr, Device *dev);

void vm_step(Vm *vm);
