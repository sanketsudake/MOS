#include"cpu.h"
CPU* cpu_init(CPU *cpu){
  cpu=(CPU*)malloc(sizeof(CPU));
  if(cpu==NULL)
    {
      fprintf(stderr,"Memory not allocated");
    }
  return cpu;
}
