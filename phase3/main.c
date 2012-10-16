/****************************************************/
/* File name:-main.c                                */
/* Licence:- GNU GPL v3                             */
/* Project Name:-Multiprogramming  Operating System */
/* **************************************************/

#include"mos.h"
#include"cpu.h"
#include"linep.h"
#include"card.h"
int main(){
  HAL *hal=NULL;
  char instream[]="input.txt";
  char outstream[]="output.txt";
  hal=hal_turnon(hal,instream,outstream);
  /* Read and execute cycle */
  while(1){
    card_read(hal->instream,hal->memory,hal->pcb,hal->cpu);
    mos_execute(hal);
  }
  hal_turnoff(hal);
  return 0;
} /* End of main */
