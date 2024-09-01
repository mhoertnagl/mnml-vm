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
#define NEXT_ARG() (     \
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
#define PUSHC(val) (*vm.cp = (val), vm.cp++)
// #define POPC()     (*(--vm.cp))
#define PEEKC(off) (*(vm.fp + (off)))
#define BINOPI(op) u64 r = POPD(); PEEKD() op##= r
#define BINOP(op)  u64 r = POPD(); PEEKD() = PEEKD() op r

Vm vm;

VmResult vm_run(u8 *code) {
  vm.ip = code;
  vm.dp = vm.dat;
  vm.cp = vm.cal;
  vm.fp = vm.cal;
  for (;;) {
    // switch (NEXT_OP() & 0x1f) {
    switch (NEXT_OP()) {
      case OP_PSH:  { PUSHD(NEXT_ARG()); break; } 
      // case OP_POP:  { POPD(); break; }
      // case OP_DUP:  { PUSHD(PEEKD()); break; }
      // case OP_LDW: { PEEKD() = vm.mem[PEEKD()]; break; }
      // case OP_STW: { u64 v = POPD(); u64 a = POPD(); vm.mem[a] = v; break; }
      case OP_ADD:  { BINOPI(+); break; }
      case OP_SUB:  { BINOPI(-); break; } 
      case OP_MUL:  { BINOPI(*); break; }  
      case OP_DIV:  { BINOPI(/); break; }
      case OP_EQ:   { BINOP(==); break; }
      case OP_NE:   { BINOP(!=); break; }
      case OP_GT:   { BINOP(>);  break; }
      case OP_GE:   { BINOP(>=); break; }
      case OP_LT:   { BINOP(<);  break; }
      case OP_LE:   { BINOP(<=); break; }
      case OP_JMP:  { vm.ip = code + PEEK_ARG(); break; }
      case OP_JEZ:  { 
        u64 offset = NEXT_ARG(); 
        if (!POPD()) vm.ip = code + offset; 
        break; 
      }
      case OP_CALL: { 
        vm.cp[0] = (u64)vm.fp;
        vm.cp[1] = (u64)(vm.ip + 8 + 1);
        vm.fp    = vm.cp;
        vm.cp   += 2;
        vm.ip    = code + PEEK_ARG();
        break;
      }
      // case OP_CALL: {
      //   vm.cp[0] = (u64)vm.fp;
      //   vm.cp[1] = (u64)(vm.ip + 8 + 1);
      //   vm.ip    = code + NEXT_ARG();
      //   u64 argc = NEXT_ARG();
      //   for (u64 i = 0; i < argc; i++) {
      //     vm.cp[i + 2] = vm.dp[i - argc];
      //   }
      //   vm.fp = vm.cp;
      //   vm.cp += argc + 2;
      //   vm.dp -= argc;
      //   break; 
      // }
      case OP_RET:  { 
        vm.cp = vm.fp;
        vm.fp = (u64 *)(*vm.cp);
        vm.ip = (u8 *)(*(vm.cp + 1)); 
        break; 
      }
      case OP_PSHV: { PUSHC(POPD()); break; }
      case OP_LDV:  { PUSHD(PEEKC(NEXT_ARG())); break; }
      // case OP_LDV:  { PEEKD() = PEEKC(PEEKD()); break; }
      case OP_STV:  { PEEKC(NEXT_ARG()) = POPD(); break; }
      case OP_HLT:  return VM_SUCCESS;
      default: return VM_ERROR_UNKNOWN_OPCODE;
      // case 18 ... 31: return VM_ERROR_UNKNOWN_OPCODE;
    }
  }
}
