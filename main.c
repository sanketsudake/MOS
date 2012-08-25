#include"mos.h"
#include"cpu.h"
#include"linep.h"
#include"card.h"
int main(){
  HAL *hal;
  int count;
  char instream[]="/home/valtzar/MOS/job.txt";
  char outstream[]="/home/valtzar/MOS/output.txt";
  hal=hal_turnon(hal,instream,outstream);
  hal_turnoff(hal);
  count=card_read(hal->instream,hal->memory);
  printf("Hello valtzar\n");
  return 0;
}
