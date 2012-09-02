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
};
typedef struct HAL HAL;

/* Turn on & off  HAL to allocate or dealloc memory  */
extern HAL* hal_turnon(HAL *hal,char *instream,char *outstream);
extern void hal_turnoff(HAL *hal);

/*Executing program ... */
extern void mos_execute(HAL *hal);

/* All services  */
extern void mos_gd(HAL *hal,int addr);
extern void mos_pd(HAL *hal,int addr);
extern void mos_lr(HAL *hal,int addr);
extern void mos_sr(HAL *hal,int addr);
extern void mos_cr(HAL *hal,int addr);
extern void mos_bt(HAL *hal,int addr,int *row,int *line);
extern HAL* mos_halt(HAL *hal);
#endif  /* mos.h */
