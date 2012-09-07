/******************************************************/
/* File Name:- linep.h                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/

#ifndef LINEP_H_
#define LINEP_H_
#include"card.h"
/* LINEPRINTER Structure=>
   OPLINE=Output Line;
   OPFLAG=Check New Output Available,Or Halt
 */
struct LINEPRINTER{
  char OPLINE[42];
  int OPFLAG;
};
typedef struct LINEPRINTER LINEPRINTER;

/* Functions for lineprinter */
extern LINEPRINTER* linep_init(LINEPRINTER *linep);
extern FILE* linep_open(FILE *FOUT,char *filename);
extern void linep_close(FILE *FOUT);
extern void linep_print(FILE *FOUT,LINEPRINTER *linep);
extern void linep_jobend(FILE *FOUT);

#endif  /* linep.h */
