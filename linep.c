/******************************************/
/* Author:-Sanket Sudake                  */
/* Licence:- GNU GPL v3                   */
/* Project Name:-Machine Operating System */
/* ****************************************/

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
  memset((void*)(*linep).OPLINE,'\0',sizeof(char)*42);
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
  int i;
  if(FOUT && linep->OPFLAG)
    {
      fseek(FOUT,0,SEEK_END);
      for(i=0;i<strlen(linep->OPLINE)+1;i++)
        if(linep->OPLINE[i]=='\n')
          {
            linep->OPLINE[i]='\0';
          }
      fprintf(FOUT,"%s\n",linep->OPLINE);
    }
  linep->OPFLAG=0;
}

void linep_jobend(FILE *FOUT){
  if(FOUT)
    {
      fseek(FOUT,0,SEEK_END);
      fprintf(FOUT,"\n\n");
    }
}
