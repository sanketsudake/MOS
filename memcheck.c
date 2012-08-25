#include"mem.h"
#include"card.h"
int main(){
  MEM *memory=NULL;
  FILE *FIN;
  char filename[]="/home/valtzar/job.txt";
  int count=0,i=0;
  memory=mem_init(memory);
  FIN=card_open(FIN,filename);
  count=card_read(FIN,memory);
  printf("count = %d\n",count);
  printf("%c\n",mem_getchar(memory,1,1));
  printf("%c\n",meml_getchar(memory,1));
  card_close(FIN);
  for(i=0;i<3;i++){
    printf("%s\n",memory->BUFF[i]);
  }
  return 0;
}
