/******************************************************/
/* File Name:- card.c                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#include"card.h"
#include"mos.h"
/* Open card using filename */
FILE*
card_open(FILE *FIN,char *filename){
  FIN=fopen(filename,"rt");
  if(FIN==0){
    fprintf(stderr,"\ncard_open:Can't Open Input File");
    exit(8);
  }
  return FIN;
}
/* Read card up $DTA and store in buffer */
int
card_read(FILE *FIN,MEM *memory,PCB *pcb,CPU *cpu){
  int count=0,temp=0,r_no=0,dtaflag=0,i=0;
  r_no=mem_random(memory);
  mem_pcount(memory,r_no);
  cpu->PTR=r_no;
  for(i=0;i<42;i++)
    memory->MMEM[r_no][i]=0;
  while(fgets(memory->LINE,(int)sizeof(memory->LINE),FIN)){
    if((*memory).LINE[0]=='$'){
      switch(memory->LINE[1]){
      case 'A':pcb_set((*memory).LINE,pcb);
        break;
      case 'D':temp++;
        dtaflag=1;
        break;
      case 'E':fprintf(stdout,"\ncard_read:Dirty Read :-(");
        return 0;
        break;
      default:fprintf(stdout,"\ncard_read:Case not found for $ statement");
      }
    }
    if(dtaflag)
      break;
    if((*memory).LINE[0]!='$'){
      r_no=mem_random(memory);
      mem_pcount(memory,r_no);
      memory->MMEM[cpu->PTR][count*4+0]=0;
      memory->MMEM[cpu->PTR][count*4+1]=1;
      memory->MMEM[cpu->PTR][count*4+2]=r_no/10;
      memory->MMEM[cpu->PTR][count*4+3]=r_no%10;
      strcpy(&((*memory).MMEM[r_no][0]),(*memory).LINE);
      count++;
    }
    else{
      temp++;
    }
  }
  switch(temp){
  case 0:fprintf(stdout,"\ncard_read:End of jobs :-)");
    exit(8);
    break;
  case 1:fprintf(stdout,"\ncard_read:Check for $AMJ,$DTA in Program :-(");
    exit(8);
    break;
  case 2:fprintf(stdout,"\ncard_read:Program contains $AMJ,$DTA");
    break;
  default:fprintf(stdout,"\ncard_read:Case not found for temp");
  }
  count=0;
  dtaflag=cpu->PTR;
  fprintf(stdout,"\nPTR=%d",cpu->PTR);
  while(memory->MMEM[dtaflag][count*4+1]==1){
    r_no=memory->MMEM[dtaflag][count*4+2]*10+memory->MMEM[dtaflag][count*4+3];
    fprintf(stdout,"%d\t%s",r_no,memory->MMEM[r_no]);
    count++;
  }
  fprintf(stdout,"\n");
  return count;
}
/* Close cardreader */
void
card_close(FILE *FIN){
  if(FIN){
    fclose(FIN);
  }
}
