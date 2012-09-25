/******************************************************/
/* File Name:- cpu.c                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#include"cpu.h"
/* Innitialize cpu */
CPU*
cpu_init(CPU *cpu){
  if(cpu==NULL)
    cpu=(CPU*)malloc(sizeof(CPU));
  if(cpu==NULL)
    fprintf(stderr,"cpu_init:Memory not allocated");
  cpu->IC=0;
  cpu->TTC=0;
  cpu->TLC=0;
  memset((void*)cpu->IR,'\0',sizeof(char)*4);
  memset((void*)cpu->R,'\0',sizeof(char)*4);
  cpu->SI=3;
  cpu->PI=0;
  cpu->TI=0;
  cpu->PTR=0;
  cpu->MODE=slave;
  cpu->C=f;
  return cpu;
}
/* Print error message */
void
cpu_em(int n,FILE *FOUT)
{
  fseek(FOUT,0,SEEK_END);
  switch(n)
    {
    case 0:
      fputs("\ncpu_em:No Error",FOUT);
      break;
    case 1:
      fputs("\ncpu_em:Out of Data",FOUT);
      break;
    case 2:
      fputs("\ncpu_em:Line Limit Exceeded",FOUT);
      break;
    case 3:
      fputs("\ncpu_em:Time Limit Exceeded",FOUT);
      break;
    case 4:
      fputs("\ncpu_em:Operation Code Error",FOUT);
      break;
    case 5:
      fputs("\ncpu_em:Operand Error",FOUT);
      break;
    case 6:
      fputs("\ncpu_em:Invalid Page Fault",FOUT);
      break;
    default:
      fputs("\ncpu_em:No specified error format",FOUT);
    }
}
