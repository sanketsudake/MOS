#ifndef CPU_H_
#define CPU_H_
#include"mem.h"

/*CPU Structure=>
  IR=Instruction Register,
  R=CPU Register,
  SI=System Interrupt,
  PI=Program Interrupt,
*/
struct CPU{
  int PC;
  char IR[4],R[4];
  enum SI {none,gd,pd,h} SI;
  enum PI{n,y}PI;
  enum MODE{master,slave}MODE;
  enum TOGGLE{true,false}C;
  /* enum TI=Second Phase */
};
typedef struct CPU CPU;

extern CPU* cpu_init(CPU *cpu);
#endif  /* cpu.h int addr*/
