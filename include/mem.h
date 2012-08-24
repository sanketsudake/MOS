#ifndef MEM_H_
#define MEM_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* MEMORY structure=>
   BUFF Buffer Containing 10 words
   LINE To Read Line From Program
 */
struct MEM{
  char BUFF[10][41];
  char LINE[41];
  char *MEMPTR;
};
typedef struct MEM MEM;
MEM *memory;
extern void mem_init(MEM *memory);
extern char mem_getchar(MEM *memory,int row,int coloumn);
extern char meml_getchar(MEM *Memory,int no);
#endif  /* mem.h */
