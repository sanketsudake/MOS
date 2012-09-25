/******************************************************/
/* File Name:- mem.c                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#include"mem.h"
/* Allocate Memory */
static MEM*
mem_alloc(MEM *memory){
  if(memory==NULL)
    memory=(MEM*)malloc(sizeof(MEM));
  if(memory==NULL)
    {
      fprintf(stderr,"mem_alloc:Memory not allocated");
      exit(8);
    }
  return memory;
}
/* Set Whole Memory To Blank */
static MEM*
mem_set(MEM *memory){
  memset((void*)memory->MMEM,'\0',sizeof(char)*30*42);
  memset((void*)memory->LINE,'\0',sizeof(char)*42);
  memset((void*)memory->mtemp,'\0',sizeof(char)*4);
  memset((void*)memory->randlist,-1,sizeof(int)*10);
  memory->pcount=0;

  return memory;
}
/* Innitialize Memory */
MEM*
mem_init(MEM *memory){
 memory=mem_alloc(memory);
 memory=mem_set(memory);

 return memory;
}
/* Get A Character From Current Memory Line*/
inline char
meml_getchar(MEM *memory,int no){
  return (*memory).LINE[no];
}
/* Get A Character From Main Memory */
inline char
memm_getchar(MEM *memory,int line,int place){
  return (*memory).MMEM[line][place];
}
/* Get Random Address Checked Before Allocation */
static int
mem_randcheck(MEM *memory,int r_no)
{
  int i;
  for (i=0;memory->randlist[i]!=-1;i++)
    if(memory->randlist[i]==r_no)
      return 0;
  return 1;
}
/* Get A Random Number Between 0 to 30 */
int
mem_random(MEM *memory)
{
  int r_no,correct=0;

  while(correct==0){
    r_no=random()%30;
    if(mem_randcheck(memory,r_no))
      {
        correct=1;
        return r_no;
      }
  }
  printf("mem_random:Sorry cant generate random no.\n");
  return -1;
}
/* Update pcount variable for synchronized random no generation */
inline void
mem_pcount(MEM *memory,int no){
  memory->randlist[memory->pcount]=no;
  memory->pcount+=1;

}
