/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/
#ifndef MOS_H_
#define MOS_H_
#include"cpu.h"
#include"mem.h"
#include"card.h"
#include"linep.h"
struct HAL{
  CPU *cpu;
  MEM *memory;
  LINEPRINTER *linep;
  FILE *instream;
  FILE *outstream;
  int flag;
  int gd[10];
};
typedef struct HAL HAL;

extern HAL* hal_turnon(HAL *hal,char *instream,char *outstream);
extern void hal_turnoff(HAL *hal);
extern HAL* mos_halt(HAL *hal);
extern void mos_gd(HAL *hal,int addr);
extern void mos_pd(HAL *hal,int addr);
extern void mos_execute(HAL *hal);
extern void mos_call(HAL *hal,int *row,int *line);
extern void mos_lr(HAL *hal,int addr);
extern void mos_sr(HAL *hal,int addr);
extern void mos_cr(HAL *hal,int addr);
extern void mos_bt(HAL *hal,int addr,int *row,int *line);
#endif  /* mos.h */
