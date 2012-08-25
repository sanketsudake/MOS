#ifndef LINEP_H_
#define LINEP_H_
#include"card.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* LINEPRINTER Structure=>
   OPLINE=Output Line;
   OPFLAG=Check New Output Available,Or Halt
 */
struct LINEPRINTER{
  char OPLINE[40];
  int OPFLAG;
};
typedef struct LINEPRINTER LINEPRINTER;
extern void line_set(LINEPRINTER *linep);
extern void line_open(FILE *FOUT,char *filename);
extern void linep_close(FILE *FOUT);
extern void linep_print(FILE *FOUT,char *LINE,int OPFLAG);

/* static void linep_set(LINEPRINTER *linep){
   memset((*linep).OPLINE,'\0',sizeof((*linep).OPLINE));
} */

#endif  /* linep.h */
