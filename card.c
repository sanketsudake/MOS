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
  int count=0,temp=0,i=0;
  while(fgets(memory->LINE,(int)sizeof(memory->LINE),FIN)){
    if(strlen((*memory).LINE)==0){
      printf("\nEnd Of the Jobs. :-)\n");
      exit(8);
    }
    if((*memory).LINE[0]=='$'&&(*memory).LINE[1]=='E'){
      printf("Error:In card_read function ");
      return 0;
    }
    if((*memory).LINE[0]=='$'&&(*memory).LINE[1]=='D'){
        temp++;
        break;
      }
    if((*memory).LINE[0]!='$'){
      for(i=0;i<strlen(memory->LINE)+1;i++)
        if(memory->LINE[i]=='\n'){
            memory->LINE[i]='\0';
          }
      strcpy(&((*memory).BUFF[count][0]),(*memory).LINE);
      count++;
    }
    else{
      temp++;
    }
  }
  if(temp<2){
      fprintf(stderr,"Error:Check for $AMJ,$DTA,$END in Program :-(");
      exit(8);
    }
  printf("\ncount=%d\n",count);
  for(i=0;i<count;i++){
    printf("%s\n",memory->BUFF[i]);
  }
  return count;
}

/* Close cardreader */
void card_close(FILE *FIN){
  if(FIN){
    CLOSE(FIN);
  }
}
