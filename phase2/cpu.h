/******************************************************/
/* File Name:- cpu.h                                  */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#ifndef CPU_H_
#define CPU_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*CPU Structure=>
  PC=Program Counter,
  TTC=Total Time Counter,
  TLC=Total Line Limit,
  IR=Instruction Register,
  R=CPU Register,
  PTR=Page Table Register,
  SI=System Interrupt,
  PI=Program Interrupt,
  TI=Time Interrupt
*/
struct CPU{
  unsigned int IC,TTC,TLC,SI,PI,TI,PTR;
  char IR[4],R[4];
  enum MODE{master,slave}MODE;
  enum TOGGLE{t,f}C;
};
typedef struct CPU CPU;
/* Cpu functions */
extern CPU* cpu_init(CPU *cpu);
extern void cpu_em(int n,FILE *FOUT);
#endif  /* cpu.h int addr*/
