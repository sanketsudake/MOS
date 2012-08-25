#ifndef CPU_H_
#define CPU_H_
/*CPU Structure=>
  IR=Instruction Register,
  R=CPU Register,
  SI=System Interrupt,
  PI=Program Interrupt,
*/
struct CPU{
  char IR[4],R[4];
  int PC;
  enum SI{0,1,2,3}SI;
  enum PI{0,1}PI;
  /* enum TI=Second Phase */
  enum MODE{master,slave}MODE;
  enum TOGGLE{true,false}C;
};
typedef struct CPU CPU;
extern void cpu_init();
#endif  /* cpu.h */
