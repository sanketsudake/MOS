#include"mos.h"
#include<ctype.h>
/* Turn on hardware abstraction layer */
HAL* hal_turnon(HAL *hal,char *instream,char *outstream){
  hal=(HAL*)malloc(sizeof(HAL));
  if(hal==NULL){
    fprintf(stderr,"Memory not allocated");
  }
  hal->memory=mem_init(hal->memory);
  hal->cpu=cpu_init(hal->cpu);
  hal->linep=linep_init(hal->linep);
  hal->instream=card_open(hal->instream,instream);
  hal->outstream=linep_open(hal->outstream,outstream);
  hal->flag=0;
  memset((void*)hal->gd,0,sizeof(int)*10);
  return hal;
}

/* Free Overall Memory */
void  hal_turnoff(HAL *hal){
  card_close(hal->instream);
  linep_close(hal->outstream);
  if(hal!=NULL){
    free(hal->cpu);
    free(hal->linep);
    free(hal->memory);
    free(hal);
  }
}

/* Innitialize mos in intermediate stages */
static HAL* mos_init(HAL *hal){
  if(hal->flag){
    hal->memory=mem_init(hal->memory);
    hal->cpu=cpu_init(hal->cpu);
    hal->linep=linep_init(hal->linep);
    memset((void*)hal->gd,0,sizeof(int)*10);
  }
  return hal;
}

/* Halt Service */
HAL* mos_halt(HAL *hal){
  if(hal->cpu->SI!=h && hal->cpu->PI!=y){
    fprintf(stderr,"error in call");
    exit(8);
  }
  linep_jobend(hal->outstream);
  hal->flag=1;
  hal=mos_init(hal);
  return hal;
}


/* Get Data Service */
void mos_gd(HAL *hal,int addr){
  if(hal->cpu->SI!=gd && hal->cpu->PI!=y){
    fprintf(stderr,"error in call");
    exit(8);
  }
  if((int)(addr/10)<10){
    hal->gd[(int)addr/10]=1;
  }
}

/* Print Data Service */
void mos_pd(HAL *hal,int addr){
  int temp;
  if(hal->cpu->SI!=pd && hal->cpu->PI!=y){
    fprintf(stderr,"error in call");
    exit(8);
  }
  temp=addr/10;
  if(hal->gd[temp]==1){
    strcpy(hal->linep->OPLINE,hal->memory->BUFF[temp]);
    hal->linep->OPFLAG=1;
  }
}


void mos_execute(HAL *hal){
  int row=0,line=0,cno=0;
  char c;
  while(1)
    {
      if(row==41){
        line+=1;
        if(line==10)
          {
            fprintf(stderr,"Program overflow");
            exit(8);
          }
        row=0;
      }
      c=mem_getchar(hal->memory,line,row);
      if(c=='H' && cno==0)
        {
          hal->cpu->SI=h;
          mos_halt(hal);
          return;
        }
      if(isalnum(c))
        {
          /* printf("\n%d\t%c\t%d\t%d\t%d\t%d\n",cno,c,isalpha(c),isdigit(c),row,line); */
          if(isalpha(c) && cno<=2)
            {
              hal->cpu->IR[cno]=c;
            }
          if(isalpha(c) && (cno==2||cno==3))
            {
              hal->cpu->PI=n;
              fprintf(stderr,"Incorrect Program");
              exit(8);
            }
          if(isdigit(c) && 2<cno<=4)
            {
              hal->cpu->IR[cno]=c;
            }
          if(isdigit(c) && (cno==0||cno==1))
            {
              hal->cpu->PI=n;
              fprintf(stderr,"Incorrect Program");
              exit(8);
            }
          cno++;
        }

      if(cno==4)
        {
          mos_call(hal);
          cno=0;
        }
      row++;
    }
}

void mos_call(HAL *hal){
  char i1,i2,i3,i4;
  int addr;
  i1=hal->cpu->IR[0];
  i2=hal->cpu->IR[1];
  i3=hal->cpu->IR[2];
  i4=hal->cpu->IR[3];
  addr=atoi(&i3)+atoi(&i4);
  printf("%d\n",addr);
  if(i1=='G' && i2=='D'){
    hal->cpu->SI=gd;
    mos_gd(hal,addr);
  }
  if(i1=='P' && i2=='D'){
    hal->cpu->SI=pd;
    mos_gd(hal,addr);
  }

}

/* /\* Load Register Service *\/ */
/* void mos_lr(CPU *cpu,int addr){ */
/*   if(cpu->PI!=y){ */
/*     printf(stderr,"error in call"); */
/*     exit(8); */
/*   } */
/* } */

/* /\* Store Register Service *\/ */
/* void mos_sr(CPU *cpu,int addr){ */
/*   if(cpu->PI!=y){ */
/*     printf(stderr,"error in call"); */
/*     exit(8); */
/*   } */
/* } */

/* /\* Compare Register Service *\/ */
/* void mos_cr(CPU *cpu,int addr){ */
/*   if(cpu->PI!=y){ */
/*     printf(stderr,"error in call"); */
/*     exit(8); */
/*   } */
/* } */

/* /\* Branch Toggle Service *\/ */
/* void mos_bt(CPU *cpu,int addr){ */
/*   if(cpu->PI!=y){ */
/*     printf(stderr,"error in call"); */
/*     exit(8); */
/*   } */
/* } */
