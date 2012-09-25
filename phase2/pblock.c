/******************************************************/
/* File Name:- pblock.c                              */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
# include"pblock.h"
/* Allocate and innitialize process control block */
PCB*
pcb_init(PCB *pcb)
{
  if(pcb==NULL)
    pcb=(PCB*)malloc(sizeof(PCB));
  if(pcb==NULL)
      printf("pcb_init:Memory not allocated");
  pcb->job_id=0;
  pcb->TTL=0;
  pcb->TLL=0;
  memset((void*)(*pcb).temp,'\0',sizeof(char)*4);
  return pcb;
}
/* Set pcb at start of each process */
void
pcb_set(char *LINE,PCB *pcb)
{
  /*  hal->mem->LINE  Here we get*/
  /* Extract job id */
  pcb->temp[0]=LINE[4];
  pcb->temp[1]=LINE[5];
  pcb->temp[2]=LINE[6];
  pcb->temp[3]=LINE[7];
  pcb->job_id=atoi(pcb->temp);
  /* Extract Total Time limit */
  pcb->temp[0]=LINE[8];
  pcb->temp[1]=LINE[9];
  pcb->temp[2]=LINE[10];
  pcb->temp[3]=LINE[11];
  pcb->TTL=atoi(pcb->temp);
  /* Extract Total Line Limit */
  pcb->temp[0]=LINE[12];
  pcb->temp[1]=LINE[13];
  pcb->temp[2]=LINE[14];
  pcb->temp[3]=LINE[15];
  pcb->TLL=atoi(pcb->temp);
  printf("pcb_set:JOB_ID=%d\tTTL=%d\tTLL=%d\n",pcb->job_id,pcb->TTL,pcb->TLL);
}
