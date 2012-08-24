#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define O_READ "rt"             /* Open File in Read Mode */
#define O_WRITE "wt"            /* Open File in Write Mode */
typedef struct cpu{
  char ir[4],reg[4];
  enum mode {master,slave}m1;
  int pc;
  enum toggle {true,false} c;
  int si;
}cpu;
cpu *cpu_init();
int main(){
  FILE *fp;
  FILE *fout;
  char *line_ptr,line[41];
  cpu *pro1;
  char buff[10][40];
  char in_file[]="/home/valtzar/job.txt";
  int count=0,i,j;
  system("ruby /home/valtzar/eg.rb");
  fin=fopen(in_file,O_READ);
  if(fin==0)
    {
      fprintf(stderr,"File Opening Eraror");
      exit(8);
    }
  while(fgets(line,sizeof(line),fin))
    {
      line[strlen(line)-1]='\0';
      strcpy(&buff[count][0],line);
      count++;
    }
  for(i=0;i<count;i++)
    {
      printf("%s\n",&buff[i][0]);
    }
  for(i=0;i<count;i++)
    {
      strcpy(line,&buff[i][0]);
      for(j=0;j<=strlen(line);++j)
        {
          if(line[j-1]!='\n')printf("%c",line[j-1]);
          if(j && j%4==0)printf(" ");
        }
    }
  close(fin);
  pro1=cpu_init();
  return 0;
}
cpu *cpu_init(){
  cpu *ptr;
  ptr=(cpu*)malloc(sizeof(cpu));
  ptr->pc=0;
  ptr->c=true;
  ptr->si=0;
  ptr->m1=slave;
  strcpy(ptr->ir,"");
  strcpy(ptr->reg,"");
  return(ptr);
}
