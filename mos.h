#ifndef MOS_H_
#define MOS_H_
#include"cpu.h"
#include"mem.h"
#include"card.h"
extern void mos_gd(CPU *cpu,int addr);
extern void mos_pd(CPU *cpu,int addr);
extern void mos_lr(CPU *cpu,int addr);
extern void mos_sr(CPU *cpu,int addr);
extern void mos_cr(CPU *cpu,int addr);
extern void mos_bt(CPU *cpu,int addr);
extern void mos_halt(CPU *cpu,int addr);

#endif  /* mos.h */
