#ifndef LINEP_H_
#define LINEP_H_
#include"card.h"
/* LINEPRINTER Structure=>
   OPLINE=Output Line;
   OPFLAG=Check New Output Available,Or Halt
 */
struct LINEPRINTER{
  char OPLINE[40];
  int OPFLAG;
};
typedef struct LINEPRINTER LINEPRINTER;
extern LINEPRINTER* linep_init(LINEPRINTER *linep);
extern FILE* linep_open(FILE *FOUT,char *filename);
extern void linep_close(FILE *FOUT);
extern void linep_print(FILE *FOUT,LINEPRINTER *linep);
extern void linep_jobend(FILE *FOUT);

#endif  /* linep.h */
