#include"linep.h"
int main(){
  LINEPRINTER *linep;
  FILE *FOUT;
  char filename[]="/home/valtzar/MOS/output.txt";
  linep=linep_init(linep);
  FOUT=linep_open(FOUT,filename);
  linep->OPFLAG=0;
  strcpy(linep->OPLINE,"This is MOS machine");
  linep_print(FOUT,linep);
  linep_jobend(FOUT);
  linep->OPFLAG=1;
  linep_print(FOUT,linep);
  linep_close(FOUT);
  return 0;
}
