#include"mos.h"


void mos_gd(CPU *cpu,int addr){
  if(cpu->SI!=gd && cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
void mos_pd(CPU *cpu,int addr){
  if(cpu->SI!=pd && cpu->!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
void mos_lr(CPU *cpu,int addr){
  if(cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
void mos_sr(CPU *cpu,int addr){
  if(cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
void mos_cr(CPU *cpu,int addr){
  if(cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }

}
void mos_bt(CPU *cpu,int addr){
  if(cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
void mos_halt(CPU *cpu,int addr){
  if(cpu->SI!=h && cpu->PI!=y){
    printf(stderr,"error in call");
    exit(8);
  }
}
