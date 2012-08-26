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
  char BUFF[10][41];
  char LINE[41];
};
typedef struct MEM MEM;
extern MEM* mem_init(MEM *memory);
extern char mem_getchar(MEM *memory,int line,int place);
extern char meml_getchar(MEM *memory,int no);
#endif  /* mem.h */
