#include"mos.h"
#include"cpu.h"
#include"linep.h"
#include"card.h"
int main(){
  HAL *hal=NULL;
  char instream[]="/home/valtzar/MOS/job.txt";
  char outstream[]="/home/valtzar/MOS/output.txt";
  hal=hal_turnon(hal,instream,outstream);
  while(1){
    card_read(hal->instream,hal->memory);
    mos_execute(hal);
  }
  hal_turnoff(hal);
  return 0;
}
