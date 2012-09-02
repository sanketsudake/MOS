/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/
#ifndef MEM_H_
#define MEM_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
/* MEMORY structure=>
   BUFF Buffer Containing 10 words
   LINE To Read Line From Program
 */
struct MEM{
  char BUFF[20][42];
  char MMEM[10][42];
  char LINE[42];
};
typedef struct MEM MEM;
extern MEM* mem_init(MEM *memory);
extern char inline  mem_getchar(MEM *memory,int line,int place);
extern char inline meml_getchar(MEM *memory,int no);
extern char inline memm_getchar(MEM *memory,int line,int place);
#endif  /* mem.h */
