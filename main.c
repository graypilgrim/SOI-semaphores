#include "main.h"
#include "producers.h"
#include "consumer.h"
#include "tools.h"

int main()
{
  int i;

  if(init() < 0)
    return -1;

  create_prod(&producerA);
  create_prod(&producerB);
  create_prod(&producerC);


  for(i = 0; i < 6; ++i)
    create_cons(i);

  while(1)
  {
  /*  printBars();*/
    usleep(70 * 10000);
    
  }

  return 0;
}
