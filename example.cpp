/*
  We define a simple bytecode language, which operates on a single variable x.
  OP0: x = 1000000000
  OP1: x = x - 1
  OP2: x = x - 2
  OP3: x = x - 3
  OP4: x = x - 4
  OP5: x = x - 5
  OP6: x = x - 6
  OP7: x = x - 7
  OP8: x = x - 8
  OP9 [1-byte addr]: if x >= 0 jmp [addr]
  OP10: return
*/

#include <cstdio>

#define OPCODE(name, num) name,
enum {
#include "opcodes.def"
};
#undef OPCODE

int switch_loop(int bytecode[]) {
  int pc = 0;
  int x = 0;
  while (1) {
    switch (bytecode[pc]) {
      case OP0: {
        x = 1000000000;
        break;
      }
      case OP1: {
        x -= 1;
        break;
      }
      case OP2: {
        x -= 2;
        break;
      }
      case OP3: {
        x -= 3;
        break;
      }
      case OP4: {
        x -= 4;
        break;
      }
      case OP5: {
        x -= 5;
        break;
      }
      case OP6: {
        x -= 6;
        break;
      }
      case OP7: {
        x -= 7;
        break;
      }
      case OP8: {
        x -= 8;
        break;
      }
      case OP9: {
        if (x >= 0) {
          pc = bytecode[pc + 1];
        }
        break;
      }
      case OP10: {
        return x;
      }
    }
    pc++;
  }
}

int indirect_threading_loop(int bytecode[]) {
  int pc = 0;
  int x = 0;
  static void *opcodeDispatch[] = {
#define OPCODE(name, num) &&case_##name,
#include "opcodes.def"
  };
#define DISPATCH  \
  pc++;           \
  goto *opcodeDispatch[bytecode[pc]];

goto *opcodeDispatch[bytecode[0]];
case_OP0:
  x = 1000000000;
  DISPATCH
case_OP1:
  x -= 1;
  DISPATCH
case_OP2:
  x -= 2;
  DISPATCH
case_OP3:
  x -= 3;
  DISPATCH
case_OP4:
  x -= 4;
  DISPATCH
case_OP5:
  x -= 5;
  DISPATCH
case_OP6:
  x -= 6;
  DISPATCH
case_OP7:
  x -= 7;
  DISPATCH
case_OP8:
  x -= 8;
  DISPATCH
case_OP9:
  if (x >= 0) {
    pc = bytecode[pc + 1];
  }
  DISPATCH
case_OP10:
  return x;
}

int main() {
  int bytecode[] = {OP0, OP1, OP2, OP3, OP4, OP5, OP6, OP7, OP8, OP9, 1, OP10};
  printf("%d\n", switch_loop(bytecode));
  //printf("%d\n", indirect_threading_loop(bytecode));
}
