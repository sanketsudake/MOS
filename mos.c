/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/
#include"mos.h"
#include<ctype.h>

/* ************************************************** */
/* Turn on & off HAL to allocate and deallocate memory */
/* Turn on hardware abstraction layer */
HAL* hal_turnon(HAL *hal,char *instream,char *outstream){
  hal=(HAL*)malloc(sizeof(HAL));
  if(hal==NULL){
    fprintf(hal->outstream,"\nhal_turnon=>Memory not allocated\t");
  }
  hal->memory=mem_init(hal->memory);
  hal->cpu=cpu_init(hal->cpu);
  hal->linep=linep_init(hal->linep);
  hal->instream=card_open(hal->instream,instream);
  hal->outstream=linep_open(hal->outstream,outstream);
  hal->flag=0;
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
/* ************************************************** */

/* ************************************************** */
/* Static functions for mos execute */
/* Innitialize mos in intermediate stages */
static HAL* mos_init(HAL *hal){
  if(hal->flag){
    hal->memory=mem_init(hal->memory);
    hal->cpu=cpu_init(hal->cpu);
    hal->linep=linep_init(hal->linep);
  }
  return hal;
}

/* Handling all interrupts after each instruction */
static void mos_interrupt(HAL *hal,int addr){
  if(hal->cpu->SI!=none)
    {
      if(hal->cpu->SI==gd)
        mos_gd(hal,addr);
      if(hal->cpu->SI==pd){
        mos_pd(hal,addr);
        linep_print(hal->outstream,hal->linep);
        hal->linep->OPFLAG=0;
      }
      if(hal->cpu->SI==h)
        mos_halt(hal);
    }
  hal->cpu->SI=none;
  if(hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_interrupt=> PI==y\t");
    mos_halt(hal);
  }
}

/* Decide which instruction does IR really contains */
static void mos_call(HAL *hal,int *row,int *line){
  char i1,i2,i3,i4,temp[2]="";
  int addr=0;
  i1=hal->cpu->IR[0];
  i2=hal->cpu->IR[1];
  i3=hal->cpu->IR[2];
  i4=hal->cpu->IR[3];
  temp[0]=i3;
  temp[1]=i4;
  addr=atoi(temp);
  printf("%d\n",addr);
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
/* ************************************************** */


/* ************************************************** */
/* MOS execute  */
/* Call to execute program after loading in memory */
void mos_execute(HAL *hal){
  int row=0,line=0,cno=0;
  char c;
  printf("\nCno\tC\tisalpha\tisdigit\trow\tline");
  while(1){
    if(row==40){
      line+=1;
      if(line==10){
        fprintf(hal->outstream,"\nmos_execute=>line==10\t");
        mos_halt(hal);
      }
      row=0;
    }
    c=mem_getchar(hal->memory,line,row);
    if(c=='H' && cno==0){
      hal->cpu->SI=h;
      mos_halt(hal);
      return;
    }
    if(isalnum(c)){
      printf("\n%d\t%c\t%d\t%d\t%d\t%d",cno,c,isalpha(c),isdigit(c),row,line);
      if(isalpha(c) && (cno==0||cno==1)){
        hal->cpu->IR[cno]=c;
      }
      if(isalpha(c) && (cno==2||cno==3)){
        hal->cpu->PI=y;
        fprintf(hal->outstream,"\nmos_execute:PI==y cno error\t");
        mos_halt(hal);
      }
      if(isdigit(c) && (cno==2||cno==3)){
        hal->cpu->IR[cno]=c;
      }
      if(isdigit(c) && (cno==0||cno==1)){
        hal->cpu->PI=y;
        fprintf(hal->outstream,"\nmos_execute:PI==y cno error\t");
        mos_halt(hal);
      }
      cno++;
    }
    if(cno==4){
      hal->cpu->PC+=1;
      mos_call(hal,&row,&line);
      cno=0;
    }
    row++;
  }
}
/* ************************************************** */


/* ************************************************** */
/* All services  */

/* Get Data Service */
void mos_gd(HAL *hal,int addr){
  if(hal->cpu->SI!=gd || hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_gd=>si!=gd\t");
    mos_halt(hal);
  }
  fgets(hal->memory->LINE,(int)sizeof(hal->memory->LINE),hal->instream);
  if(meml_getchar(hal->memory,0)=='$' && meml_getchar(hal->memory,1)=='E'){
    fprintf(hal->outstream,"\nmos_gd=>$END\t");
    mos_halt(hal);
  }
  strcpy(&(hal->memory->MMEM[(int)addr/10][(int)addr%10]),hal->memory->LINE);
  //Eg card.c          strcpy(&((*memory).BUFF[count][0]),(*memory).LINE);
}

/* Print Data Service */
void mos_pd(HAL *hal,int addr){
  if(hal->cpu->SI!=pd && hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_pd=>si!=pd\t");
    mos_halt(hal);
  }
  strcpy(hal->linep->OPLINE,&(hal->memory->MMEM[(int)addr/10][(int)addr%10]));
  hal->linep->OPFLAG=1;
}

/* Halt Service */
HAL* mos_halt(HAL *hal){
  if(hal->cpu->SI!=h && hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_halt=>si!=h\t");
    exit(8);
  }
  if(meml_getchar(hal->memory,0)!='$' && meml_getchar(hal->memory,1)!='E'){
    while(fgets(hal->memory->LINE,(int)sizeof(hal->memory->LINE),hal->instream))
      if(meml_getchar(hal->memory,0)=='$'&& meml_getchar(hal->memory,1)=='E')
        break;
  }
  fprintf(hal->outstream,"\nmos_halt=>Job finished\t");
  linep_jobend(hal->outstream);
  hal->flag=1;
  hal=mos_init(hal);
  return hal;
}

/* Load Register Service */
void mos_lr(HAL *hal,int addr){
  int temp1,temp2,i;
  if(hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_lr=>pi==y\t");
    mos_halt(hal);
  }
  temp1=(addr/10);
  temp2=(addr%10);
  for(i=0;i<4;i++){
    hal->cpu->R[i]=hal->memory->MMEM[temp1][temp2+i];
  }
}

/* Store Register Service */
void mos_sr(HAL *hal,int addr){
  int temp1,temp2,i;
  if(hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_sr=>pi==y\t");
    mos_halt(hal);
  }
  temp1=(addr/10);
  temp2=(addr%10);
  for(i=0;i<4;i++){
    hal->memory->MMEM[temp1][temp2+i]=hal->cpu->R[i];
  }
}

/* Compare Register Service */
void mos_cr(HAL *hal,int addr){
  int temp1=0,temp2=0,check_flag=1,i=0;
  if(hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_cr=>pi==y\t");
    mos_halt(hal);
  }
  temp1=(addr/10);
  temp2=(addr%10);
  for(i=0;i<4;i++)
    {
      if(hal->memory->MMEM[temp1][temp2+i]!=hal->cpu->R[i])
        {
          check_flag=0;
          break;
        }
    }
  if(check_flag)
    hal->cpu->C=true;
}

/* Branch Toggle Service */
void mos_bt(HAL *hal,int addr,int *row,int *line){
 printf("row=%d line=%d",*row,*line);
  if(hal->cpu->PI==y){
    fprintf(hal->outstream,"\nmos_bt=>pi==y\t");
    mos_halt(hal);
  }
  *row=(addr%10)*4-1;
  *line=(addr/10);
}
