#include"card.h"
#include"memory.h"
void card_open(FILE *FIN,char *filename){
  FIN=O_READ(filename);
  if(FIN==0){
    fprintf(stderr,"Error:Can't Open Input File");
    exit(8);
  }
}
int card_read(FILE *FIN,MEM *memory){
  int count,temp;
  static int lineno=0;
  count=0;
  while(fgets(memory->LINE,sizeof(memory->LINE),FIN)){
    lineno++;
    if((*memory).LINE[0]=='$'&&(*memory).LINE[1]=='E')
      break;
    if((*memory).LINE[0]!='$'){
      (*memory).LINE[strlen((*memory).LINE)-1]='\0';
      strcpy(&((*memory).BUFF[count][0]),(*memory).LINE);
      count++;
    }
    else{
      temp++;
    }
  }
  if(temp!=3)
    {
      fprintf(stderr,"Error:Check for $AMJ,$DTA,$END in Program");
      exit(8);
    }
  return count;
}
void card_close(FILE *FIN){
  if(FIN){
    CLOSE(FIN);
  }
}
