#include"card.h"
int main(){
  char buff[10][41],line[41];
  int count,i;
  FIN=O_READ("/home/valtzar/job.txt");
  if(FIN==0){
    fprintf(stderr,"FILE:Opening Error");
    exit(8);
  }
  count=0;
  memset(buff,'\0',sizeof(buff));
  memset(line,'\0',sizeof(line));
  while(fgets(line,sizeof(line),FIN)){
    if(line[0]!='$'){
      line[strlen(line)]='\0';
      strcpy(&buff[count][0],line);
    }
    count++;
  }
  for(i=0;i<count;i++){
    printf("%s",&buff[i][0]);
  }
  printf("Got here");
  CLOSE(FIN);
  return(0);
}
