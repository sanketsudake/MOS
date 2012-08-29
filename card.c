/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/

#include"card.h"
#include"memory.h"

/* Open card using filename */
FILE* card_open(FILE *FIN,char *filename){
  FIN=O_READ(filename);
  if(FIN==0){
    fprintf(stderr,"Error:Can't Open Input File");
    exit(8);
  }
  return FIN;
}

/* Read card up $END and store in buffer */
int card_read(FILE *FIN,MEM *memory){
  unsigned int count=0,temp=0;
  static unsigned int lineno=0;
  while(fgets(memory->LINE,sizeof(memory->LINE),FIN)){
    lineno++;
    if((*memory).LINE[0]=='$'&&(*memory).LINE[1]=='E')
      {
        temp++;
        break;
      }
    if((*memory).LINE[0]!='$'){
      (*memory).LINE[strlen((*memory).LINE)-1]='\0';
      strcpy(&((*memory).BUFF[count][0]),(*memory).LINE);
      count++;
    }
    else{
      temp++;
    }
  }
  if(strlen((*memory).LINE)==0)
    {
      printf("\nEnd Of the Jobs. :-)\n");
      exit(8);

    }
  if(temp!=3)
    {
      fprintf(stderr,"Error:Check for $AMJ,$DTA,$END in Program :-(");
      exit(8);
    }
  return count;
}

void card_close(FILE *FIN){
  if(FIN){
    CLOSE(FIN);
  }
}
