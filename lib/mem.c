#include"mem.h"

/* Allocate Memory */
static void mem_alloc(MEM *memory){
  memory=malloc(sizeof(MEM));
}

/* Set Whole Memory To Blank */
static void  mem_set(MEM *memory){
  memset((*memory).BUFF,'\0',sizeof((*memory).BUFF));
  memset((*memory).LINE,'\0',sizeof((*memory).LINE));
}

/* Innitialize Memory */
void mem_init(MEM *memory){
  mem_alloc(memory);
  mem_set(memory);
}

/* Get A Character From Memory Buffer */
char mem_getchar(MEM *memory,int row,int coloumn){
  return (*memory).BUFF[row][coloumn];
}

/* Get A Character From Current Memory Line*/
char meml_getchar(MEM *Memory,int no){
  return (*memory).LINE[no];
}
