/******************************************************/
/* File Name:- mem.h                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#ifndef MEM_H_
#define MEM_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include<time.h>
/* MEMORY structure=>
   BUFF Buffer Containing 10 words
   MMEM Storing user data
   LINE To Read Line From Program
 */
struct MEM{
  char MMEM[30][42];
  char LINE[42];
  char mtemp[4];
  int randlist[10];
  int pcount;
};
typedef struct MEM MEM;
/* memory functions */
extern MEM*
mem_init(MEM *memory);
extern inline
char meml_getchar(MEM *memory,int no);
extern inline
char memm_getchar(MEM *memory,int line,int place);
extern int
mem_random(MEM *memory);
extern inline
void mem_pcount(MEM *memory,int no);
/* To be implemented */
#endif  /* mem.h */
