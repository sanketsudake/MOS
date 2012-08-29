/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/
#include"mos.h"
#include<ctype.h>

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

/* Handling all interrupts after each instruction */
static void mos_interrupt(HAL *hal,int addr){
  if(hal->cpu->SI!=none)
    {
      if(hal->cpu->SI==gd)
        mos_gd(hal,addr);
      if(hal->cpu->SI==pd)
        {
          mos_pd(hal,addr);
          linep_print(hal->outstream,hal->linep);
        }
      if(hal->cpu->SI==h)
        mos_halt(hal);
    }
  if(hal->cpu->PI==y){
    fprintf(stderr,"Program Fault:Incorrect instruction");
    exit(8);
  }
}

/* Call to execute program after loading in memory */
void mos_execute(HAL *hal){
  int row=0,line=0,cno=0;
  char c;
  while(1)
    {
      if(row==41){
        line+=1;
        if(line==10)
          {
            fprintf(stderr,"Function=mos_execute:Program overflow");
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
          if(isalpha(c) && (cno==0||cno==1))
            {
              hal->cpu->IR[cno]=c;
            }
          if(isalpha(c) && (cno==2||cno==3))
            {
              hal->cpu->PI=y;
              fprintf(stderr,"Fuction=mos_execute:Incorrect Program");
              exit(8);
            }
          if(isdigit(c) && (cno==2||cno==3))
            {
              hal->cpu->IR[cno]=c;
            }
          if(isdigit(c) && (cno==0||cno==1))
            {
              hal->cpu->PI=y;
              fprintf(stderr,"Function=mos_execute:Incorrect Program");
              exit(8);
            }
          cno++;
        }

      if(cno==4)
        {
          mos_call(hal,&row,&line);
          cno=0;
        }
      row++;
    }
}

/* Decide which instruction does IR really contains */
void mos_call(HAL *hal,int *row,int *line){
  char i1,i2,i3,i4;
  int addr;
  i1=hal->cpu->IR[0];
  i2=hal->cpu->IR[1];
  i3=hal->cpu->IR[2];
  i4=hal->cpu->IR[3];
  addr=atoi(&i3)+atoi(&i4);
  /* printf("%d\n",addr); */
  if(i1=='G' && i2=='D'){
    hal->cpu->SI=gd;
  }
  if(i1=='P' && i2=='D'){
    hal->cpu->SI=pd;
  }
  if(i1=='L' && i2=='R'){
    mos_lr(hal,addr);
  }
  if(i1=='S' && i2=='R'){
    mos_sr(hal,addr);
  }
  if(i1=='C' && i2=='R'){
    mos_cr(hal,addr);
  }
  if(i1=='B' && i2== 'T'){
    mos_bt(hal,addr,row,line);
  }
  mos_interrupt(hal,addr);
}

/* Halt Service */
HAL* mos_halt(HAL *hal){
  if(hal->cpu->SI!=h && hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_halt:Error In Call");
    exit(8);
  }
  linep_jobend(hal->outstream);
  hal->flag=1;
  hal=mos_init(hal);
  return hal;
}

/* Get Data Service */
void mos_gd(HAL *hal,int addr){
  if(hal->cpu->SI!=gd && hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_gd:Error In Call");
    exit(8);
  }
  if((int)(addr/10)<10){
    hal->gd[(int)addr/10]=1;
  }
}

/* Print Data Service */
void mos_pd(HAL *hal,int addr){
  int temp;
  if(hal->cpu->SI!=pd && hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_pd:Error In Call");
    exit(8);
  }
  temp=addr/10;
  if(hal->gd[temp]==1){
    strcpy(hal->linep->OPLINE,hal->memory->BUFF[temp-1]);
    hal->linep->OPFLAG=1;
  }
}

/* Load Register Service */
void mos_lr(HAL *hal,int addr){
  int temp,i;
  if(hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_lr:Error In Call");
    exit(8);
  }
  temp=(addr/10)-1;
  for(i=0;i<4;i++){
    hal->cpu->R[i]=hal->memory->BUFF[temp][i];
  }
}

/* Store Register Service */
void mos_sr(HAL *hal,int addr){
  int temp,i;
  if(hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_sr:Error In Call");
    exit(8);
  }
  temp=(addr/10)-1;
  for(i=0;i<4;i++){
    hal->memory->BUFF[temp][i]=hal->cpu->R[i];
  }
}

/* Compare Register Service */
void mos_cr(HAL *hal,int addr){
  int temp1=0,temp2=0,flag=1,i=0;
  if(hal->cpu->PI==y){
    fprintf(stderr,"Function=mos_cr:error in call");
    exit(8);
  }
  temp1=(addr/10)-1;
  temp2=(addr%10);
  for(i=0;i<4;i++)
    {
      if(hal->memory->BUFF[temp1][temp2+i]!=hal->cpu->R[i])
        {
          flag=0;
          break;
        }
    }
  if(flag)
    hal->cpu->C=true;
}

/* Branch Toggle Service */
void mos_bt(HAL *hal,int addr,int *row,int *line){
  if(hal->cpu->PI==y){
    fprintf(stderr,"error in call");
    exit(8);
  }
  *row=addr%10;
  *line=addr/10;
}

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
