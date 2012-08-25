#include"linep.h"
void line_set(LINEPRINTER *linep){
  memset((*linep).OPLINE,'\0',sizeof((*linep).OPLINE));
}
 void line_open(FILE *FOUT,char *filename){
  FOUT=O_WRIT(filename);
  if(FOUT==NULL){
    fprintf(stderr,"Cant open output file");
    exit(8);
  }
}
 void linep_close(FILE *FOUT){
  if(FOUT)
    {
      CLOSE(FOUT);
    }
}
void linep_print(FILE *FOUT,char *LINE,int OPFLAG){
  if(FOUT && OPFLAG)
    {
      fseek(FOUT,0,SEEK_END);
      fprintf(FOUT,"%s\n",LINE);
    }
}
