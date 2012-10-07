/******************************************************/
/* File Name:- mos.c                                  */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/
#include"mos.h"
#include<ctype.h>
/* Turn on hardware abstraction layer */
HAL*
hal_turnon(HAL *hal,char *instream,char *outstream){
  if(hal==NULL)
    hal=(HAL*)malloc(sizeof(HAL));
  if(hal==NULL){
    fprintf(hal->outstream,"\nhal_turnon=>Memory not allocated");
  }
  hal->cpu=cpu_init(hal->cpu);
  hal->memory=mem_init(hal->memory);
  hal->linep=linep_init(hal->linep);
  hal->pcb=pcb_init(hal->pcb);
  hal->instream=card_open(hal->instream,instream);
  hal->outstream=linep_open(hal->outstream,outstream);
  srand(time(NULL));
  return hal;
}
/* Free Overall Memory */
void
hal_turnoff(HAL *hal){
  card_close(hal->instream);
  linep_close(hal->outstream);
  if(hal!=NULL){
    free(hal->cpu);
    free(hal->memory);
    free(hal->linep);
    free(hal->pcb);
    free(hal);
  }
}
/* Innitialize mos in intermediate stages  */
HAL*
mos_init(HAL *hal){
  hal->memory=mem_init(hal->memory);
  hal->cpu=cpu_init(hal->cpu);
  hal->linep=linep_init(hal->linep);
  hal->pcb=pcb_init(hal->pcb);
  hal->flag=0;
  return hal;
}
/* Return random for particular count line no.*/
static int
mos_line(HAL *hal,int count){
  int r_no;
  r_no=hal->memory->MMEM[hal->cpu->PTR][count*4+2]*10+hal->memory->MMEM[hal->cpu->PTR][count*4+3];
  return r_no;
}
/* Mos int handling interrupts in MOS*/
void
mos_int(HAL *hal,int addr){
  while(1){
    if(hal->cpu->TI==0 && hal->cpu->SI==1){
      mos_gd(hal,addr);
      break;
    }
    else if(hal->cpu->TI==0 && hal->cpu->SI==2){
      mos_pd(hal,addr);
      break;
    }
    else if(hal->cpu->TI==0 && hal->cpu->SI==3){
      mos_halt(hal);
      cpu_em(0,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->SI==1){
      cpu_em(3,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->SI==2){
      mos_pd(hal,addr);
      cpu_em(3,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->SI==3){
      cpu_em(0,hal->outstream);
      hal->flag=1;
      break;
    }
    else{
      break;
    }
  }
  while(1){
    if(hal->cpu->TI==0 && hal->cpu->PI==1){
      cpu_em(4,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==0 && hal->cpu->PI==2){
      cpu_em(5,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==0 && hal->cpu->PI==3){
      cpu_em(6,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->PI==1){
      cpu_em(3,hal->outstream);
      cpu_em(4,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->PI==2){
      cpu_em(3,hal->outstream);
      cpu_em(5,hal->outstream);
      hal->flag=1;
      break;
    }
    else if(hal->cpu->TI==2 && hal->cpu->PI==3){
      cpu_em(3,hal->outstream);
      hal->flag=1;
      break;
    }
    else{
      break;
    }
  }
  hal->cpu->SI=0;
  hal->cpu->PI=0;
  hal->cpu->TI=0;
}
/* Mos call Function called after each instruction loaded in IR
check if opcode and oprand are correct later on call the functions*/
int
mos_call(HAL *hal,int *row,int *line){
  char i1,i2,temp[2]="";
  int addr=0;
  i1=hal->cpu->IR[0];
  i2=hal->cpu->IR[1];
  temp[0]=hal->cpu->IR[2];
  temp[1]=hal->cpu->IR[3];
  if(!isdigit(temp[0]) || !isdigit(temp[1])){
    //cpu_em(5,hal->outstream);
    hal->flag=1;
    hal->cpu->PI=2;
    //    return 0;
  }
  addr=atoi(temp);
  fseek(hal->outstream,0,SEEK_END);
  while(1){
    if(i1=='G' && i2=='D'){
      hal->cpu->SI=1;
      break;
    }
    else if(i1=='P' && i2=='D'){
      hal->cpu->SI=2;
      break;
    }
    else if(i1=='L' && i2=='R'){
      mos_lr(hal,addr);
      break;
    }
    else if(i1=='S' && i2=='R'){
      mos_sr(hal,addr);
      break;
    }
    else if(i1=='C' && i2=='R'){
      mos_cr(hal,addr);
      break;
    }
    else if(i1=='B' && i2== 'T'){
      mos_bt(hal,addr,row,line);
      break;
    }
    else{
      hal->cpu->PI=1;
      break;
    }
  }
  hal->cpu->TTC+=1;
  if(hal->cpu->TTC==hal->pcb->TTL)
    hal->cpu->TI=2;
  mos_int(hal,addr);
  return 0;
}
/* Mos execute
Execution of each mos code, after loading into memory, starts here.
*/
void
mos_execute(HAL *hal){
  int line=0,row=0,count=0,i;
  hal->cpu->IC=0;
  line=mos_line(hal,count);
  while(1){
    if(hal->cpu->TTC>=hal->pcb->TTL)
      {
        cpu_em(3,hal->outstream);
        break;
      }

    if(row==40){
      count+=1;
      row=0;
      line=mos_line(hal,count);
    }
    hal->cpu->IR[0]=hal->memory->MMEM[line][row];
    hal->cpu->IR[1]=hal->memory->MMEM[line][row+1];
    hal->cpu->IR[2]=hal->memory->MMEM[line][row+2];
    hal->cpu->IR[3]=hal->memory->MMEM[line][row+3];
    //    printf("\nrow=%d\tline=%d\tIR=%s",row,line,hal->cpu->IR);
    row+=4;
    if(hal->cpu->IR[0]=='H'){
      hal->cpu->TTC+=1;
      hal->cpu->IC+=1;
      cpu_em(0,hal->outstream);
      break;
    }
    mos_call(hal,&row,&line);
    //    fprintf(hal->outstream,"%s\t",hal->cpu->IR);
    hal->cpu->IC+=1;
    if(hal->flag)
      break;
  }
  printf("%s",hal->memory->MMEM[hal->cpu->PTR]);
  for(i=0;i<strlen(hal->cpu->IR);i++)
    if(hal->cpu->IR[i]=='\n')
      hal->cpu->IR[i]=' ';
  fseek(hal->outstream,0,SEEK_END);
  fprintf(hal->outstream,"\nmos_execute:JID=%d IC=%d IR=%s TLC=%d\n",hal->pcb->job_id,hal->cpu->TTC,hal->cpu->IR,hal->cpu->TLC);
  mos_halt(hal);
}
/* Halt Service -halt the mos by inserting two new lines*/
HAL*
mos_halt(HAL *hal){
  if(meml_getchar(hal->memory,1)!='E'){
    while(fgets(hal->memory->LINE,(int)sizeof(hal->memory->LINE),hal->instream)){
        if(meml_getchar(hal->memory,0)=='$'&& meml_getchar(hal->memory,1)=='E')
          break;
      }
  }
  linep_jobend(hal->outstream);
  hal=mos_init(hal);
  return hal;
}
/* GD get data service allocate the block for new data ,give error if out of
the data
 */
void
mos_gd(HAL *hal,int addr){
  int temp1,temp2,r_no;
  fgets(hal->memory->LINE,(int)sizeof(hal->memory->LINE),hal->instream);
  temp1=hal->cpu->PTR;
  temp2=(addr/10)*4;
  if(hal->memory->MMEM[temp1][temp2+1]==1){
    r_no=mos_line(hal,addr/10);
  }
  else{
    r_no=mem_random(hal->memory);
    mem_pcount(hal->memory,r_no);
    hal->memory->MMEM[temp1][temp2]=0;
    hal->memory->MMEM[temp1][temp2+1]=1;
    hal->memory->MMEM[temp1][temp2+2]=r_no/10;
    hal->memory->MMEM[temp1][temp2+3]=r_no%10;
  }
  if(meml_getchar(hal->memory,0)=='$' && meml_getchar(hal->memory,1)=='E'){
    cpu_em(1,hal->outstream);
    hal->cpu->SI=3;
    hal->flag=1;
  }
  strncpy(hal->memory->MMEM[r_no],hal->memory->LINE,42);
}
/* PD print data,find random no for page and print data */
void
mos_pd(HAL *hal,int addr){
  int temp1,temp2,r_no;
  temp1=hal->cpu->PTR;
  temp2=addr/10*4;
  if(hal->memory->MMEM[temp1][temp2+1]==1){
    if(hal->cpu->TLC < hal->pcb->TLL){
      r_no=mos_line(hal,addr/10);
      strncpy(hal->linep->OPLINE,hal->memory->MMEM[r_no],42);
      hal->linep->OPFLAG=1;
      linep_print(hal->outstream,hal->linep);
      hal->cpu->TLC+=1;
    }
    else{
      cpu_em(2,hal->outstream);
      hal->flag=1;
    }
  }
  else{
    cpu_em(6,hal->outstream);
    hal->flag=1;
  }
}
/* LR load register,map particular address and get cpu register loaded with
given location */
void
mos_lr(HAL *hal,int addr){
  int temp1,r_no;
  if(hal->memory->MMEM[hal->cpu->PTR][addr/10*4+1]==1){
    r_no=mos_line(hal,addr/10);
    temp1=addr%10*4;
    hal->cpu->R[0]=hal->memory->MMEM[r_no][temp1+0];
    hal->cpu->R[1]=hal->memory->MMEM[r_no][temp1+1];
    hal->cpu->R[2]=hal->memory->MMEM[r_no][temp1+2];
    hal->cpu->R[3]=hal->memory->MMEM[r_no][temp1+3];
    hal->cpu->R[4]='\0';
  }
  else{
    cpu_em(6,hal->outstream);
    hal->flag=1;
  }
}
/* SR store register,store data in cpu register as per address given */
void
mos_sr(HAL *hal,int addr){
  int temp1,temp2,r_no;
  temp1=hal->cpu->PTR;
  temp2=addr/10*4;
  if(hal->memory->MMEM[temp1][temp2+1]!=1){
    hal->memory->MMEM[temp1][temp2+1]=1;
    r_no=mem_random(hal->memory);
    mem_pcount(hal->memory,r_no);
    hal->memory->MMEM[temp1][temp2+2]=r_no/10;
    hal->memory->MMEM[temp1][temp2+3]=r_no%10;
  }
  r_no=mos_line(hal,addr/10);
  hal->memory->MMEM[r_no][addr%10*4+0]=hal->cpu->R[0];
  hal->memory->MMEM[r_no][addr%10*4+1]=hal->cpu->R[1];
  hal->memory->MMEM[r_no][addr%10*4+2]=hal->cpu->R[2];
  hal->memory->MMEM[r_no][addr%10*4+3]=hal->cpu->R[3];

}
/* CR -compare register, compare data in register with memory location
given */
void
mos_cr(HAL *hal,int addr){
  int temp1,r_no,i,check_flag=1;
  if(hal->memory->MMEM[hal->cpu->PTR][addr/10*4+1]==1){
    r_no=mos_line(hal,addr/10);
    temp1=addr%10*4;
    for(i=0;i<4;i++)
      if(hal->cpu->R[i]!=hal->memory->MMEM[r_no][temp1+i]){
        check_flag=0;
        break;
      }
    if(check_flag){
      hal->cpu->C=t;
    }
  }
  else{
    hal->flag=1;
    cpu_em(6,hal->outstream);
  }
}
/* Branch toggle if toggle value 1 */
void
mos_bt(HAL *hal,int addr,int *row,int *line){
  int tempaddr=0,i,j,flag=0,temp1,r_no;
  if(hal->cpu->C==t){
    for(i=0;i<9;i++){
      for(j=0;j<10;j++){
        tempaddr++;
        if(tempaddr==addr)
          {
            flag=1;
            break;
          }
      }
      if(flag){
        break;
      }
    }
    temp1=hal->cpu->PTR;
    if(hal->memory->MMEM[temp1][i*4+1]==1){
      r_no=mos_line(hal,i);
    }
    *row=j*4;
    *line=r_no;
  }
}
