#ifndef LINEP_H_
#define LINEP_H_
/* LINEPRINTER Structure=>
   OPLINE=Output Line;
   OPFLAG=Check New Output Available,Or Halt
 */
struct LINEPRINTER{
  char OPLINE[40];
  int OPFLAG;
};
static void linep_set(LINEPRINTER *linep);
/* static void linep_set(LINEPRINTER *linep){
   memset((*linep).OPLINE,'\0',sizeof((*linep).OPLINE));
} */
typedef struct LINEPRINTER LINEPRINTER;
#endif  /* linep.h */
