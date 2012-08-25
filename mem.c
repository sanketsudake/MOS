#include"mem.h"

/* Allocate Memory */
static MEM* mem_alloc(MEM *memory){
  if(memory==NULL){
    memory=(MEM*)malloc(sizeof(MEM));
  }
  if(memory==NULL)
    {
      fprintf(stderr,"Memory not allocated");
      exit(8);
    }
  return memory;
}

/* Set Whole Memory To Blank */
static MEM* mem_set(MEM *memory){
  memset((void*)memory->BUFF,'\0',sizeof(char)*10*41);
  memset((void*)memory->LINE,'\0',sizeof(char)*41);
  return memory;
}

/* Innitialize Memory */
MEM* mem_init(MEM *memory){
 memory=mem_alloc(memory);
 memory=mem_set(memory);
 return memory;
}

/* Get A Character From Memory Buffer */
char mem_getchar(MEM *memory,int row,int coloumn){
  return (*memory).BUFF[row][coloumn];
}

/* Get A Character From Current Memory Line*/
char meml_getchar(MEM *memory,int no){
  return (*memory).LINE[no];
}
