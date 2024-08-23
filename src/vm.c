#include <stdint.h>
#include "vm.h"

#define NEXT_OP() (*vm.ip++)
#define PEEK_ARG() (    \
  (u64)vm.ip[0] << 56 | \
  (u64)vm.ip[1] << 48 | \
  (u64)vm.ip[2] << 40 | \
  (u64)vm.ip[3] << 32 | \
  (u64)vm.ip[4] << 24 | \
  (u64)vm.ip[5] << 16 | \
  (u64)vm.ip[6] <<  8 | \
  (u64)vm.ip[7]         \
)
#define NEXT_ARG()       \
(                        \
  vm.ip += 8,            \
  (u64)vm.ip[-8] << 56 | \
  (u64)vm.ip[-7] << 48 | \
  (u64)vm.ip[-6] << 40 | \
  (u64)vm.ip[-5] << 32 | \
  (u64)vm.ip[-4] << 24 | \
  (u64)vm.ip[-3] << 16 | \
  (u64)vm.ip[-2] <<  8 | \
  (u64)vm.ip[-1]         \
)
#define PUSHD(val) (*vm.dp = (val), vm.dp++)
#define POPD()     (*(--vm.dp))
#define PEEKD()    (*(vm.dp - 1))
#define PUSHR(val) (*vm.rp = (val), vm.rp++)
#define POPR()     (*(--vm.rp))
#define BINOPI(op) u64 r = POPD(); PEEKD() op##= r
#define BINOP(op)  u64 r = POPD(); PEEKD() = PEEKD() op r

Vm vm;

VmResult vm_run(u8 *code) {
  vm.ip = code;
  vm.dp = vm.dat;
  vm.rp = vm.ret; 
  for (;;) {
    // switch (NEXT_OP() & 0x1f) {
    switch (NEXT_OP()) {
      case OP_PSH: { PUSHD(NEXT_ARG()); break; } 
      case OP_DUP: { PUSHD(PEEKD()); break; }
      case OP_LDW: { PEEKD() = vm.mem[PEEKD()]; break; }
      case OP_STW: { u64 v = POPD(); u64 a = POPD(); vm.mem[a] = v; break; }
      case OP_ADD: { BINOPI(+); break; }
      case OP_SUB: { BINOPI(-); break; } 
      case OP_MUL: { BINOPI(*); break; }  
      case OP_DIV: { BINOPI(/); break; }
      case OP_EQU: { BINOP(==); break; }
      case OP_NEQ: { BINOP(!=); break; }
      case OP_SGT: { BINOP(>);  break; }
      case OP_SGE: { BINOP(>=); break; }
      case OP_SLT: { BINOP(<);  break; }
      case OP_SLE: { BINOP(<=); break; }
      case OP_JMP: { vm.ip = code + PEEK_ARG(); break; }
      case OP_BRA: { if (POPD()) vm.ip = code + PEEK_ARG(); break; }
      case OP_JAL: { PUSHR(vm.ip + 1); vm.ip = code + PEEK_ARG(); break; }
      case OP_RET: { vm.ip = POPR(); break; }
      case OP_HLT: return VM_SUCCESS;
      default: return VM_ERROR_UNKNOWN_OPCODE;
      // case 18 ... 31: return VM_ERROR_UNKNOWN_OPCODE;
    }
  }
}
