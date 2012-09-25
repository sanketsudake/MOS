/******************************************************/
/* File Name:- card.h                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/

#ifndef CARD_H_
#define CARD_H_
#include"mem.h"
#include"pblock.h"
#include"cpu.h"
/* Card functions */
extern FILE* card_open(FILE *FIN,char *FILENAME);
extern int card_read(FILE *FIN,MEM *memory,PCB *pcb,CPU *cpu);
extern void card_close(FILE *FIN);
#endif  /* card.h */
