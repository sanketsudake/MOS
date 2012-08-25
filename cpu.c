#include"card.h"
#include"memory.h"
void card_open(FILE *FIN,char *filename){
  FIN=O_READ(filename);
  if(FIN==0){
    fprintf("Error:Can't Open Input File");
    exit(8);
  }
}
int card_read(FILE *FIN,MEM *memory){
  int count,temp;
  count=0;
  while(fgets(memory->LINE,sizeof(memory->LINE),FIN)){
    if(memory->LINE[0]!='$'){
      line[strlen((*memory).LINE)-1]='\0';
      strcpy((*memory).&buff[count][0],line);
      count++;
    }
    else{
      temp++;
    }
  }
  if(temp!=3)
    {
      fprintf("Error:Check for $AMJ,$DTA,$END in Program");
      exit(8);
    }
  return count;
}
void card_close(FILE *FIN){
  if(FIN){
    CLOSE(FIN);
  }
}
