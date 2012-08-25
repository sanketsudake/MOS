
#include"linep.h"

static LINEPRINTER* linep_alloc(LINEPRINTER *linep){
  if(linep==NULL){
    linep=(LINEPRINTER*)malloc(sizeof(LINEPRINTER));
  }
  if(linep==NULL){
    fprintf(stderr,"Memory not allocated");
    exit(8);
  }
  return linep;
}

static LINEPRINTER* linep_set(LINEPRINTER *linep){
  memset((void*)(*linep).OPLINE,'\0',sizeof(char)*41);
  return linep;
}

LINEPRINTER* linep_init(LINEPRINTER *linep){
  linep= linep_alloc(linep);
  linep=linep_set(linep);
  return linep;
}

FILE* linep_open(FILE *FOUT,char *filename){
  FOUT=O_WRIT(filename);
  if(FOUT==NULL){
    fprintf(stderr,"Cant open output file");
    exit(8);
  }
  return FOUT;
}

void linep_close(FILE *FOUT){
  if(FOUT){
      CLOSE(FOUT);
    }
 }


void linep_print(FILE *FOUT,LINEPRINTER *linep){
  if(FOUT && linep->OPFLAG)
    {
      fseek(FOUT,0,SEEK_END);
      fprintf(FOUT,"%s\n",linep->OPLINE);
    }
}
void linep_jobend(FILE *FOUT){
  if(FOUT)
    {
      fseek(FOUT,0,SEEK_END);
      fprintf(FOUT,"\n\n");
    }
}
