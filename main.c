#include"mos.h"
#include"cpu.h"
#include"linep.h"
#include"card.h"
int main(){
  int i,count;
  HAL *hal;
  char instream[]="/home/valtzar/MOS/job.txt";
  char outstream[]="/home/valtzar/MOS/output.txt";
  hal=hal_turnon(hal,instream,outstream);
  count=card_read(hal->instream,hal->memory);
  mos_execute(hal);
  hal_turnoff(hal);
  return 0;
}
