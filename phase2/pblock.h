/******************************************************/
/* File Name:- pblock.h                                */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/

#ifndef PBLOCK_H_
#define PBLOCK_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* PCB Structure =>
 job_id=Current job id
 TTL=Total time limit
 TLL=Total line limit
*/
struct PCB
{
  int job_id;
  int TTL;
  int TLL;
  char temp[4];
};
typedef struct PCB PCB;
/* Functions for process control block */
extern PCB*
pcb_init(PCB *pcb);
extern void
pcb_set(char *LINE,PCB *pcb);
#endif  /* linep.h */
