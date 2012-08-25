#ifndef CARD_H_
#define CARD_H_
#include"mem.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define O_READ(x) fopen(x,"rt");
#define O_WRIT(x) fopen(x,"wt");
#define CLOSE(x)  fclose(x);
extern FILE* card_open(FILE *FIN,char *FILENAME);
extern int card_read(FILE *FIN,MEM *memory);
extern void card_close(FILE *FIN);
#endif  /* card.h */
