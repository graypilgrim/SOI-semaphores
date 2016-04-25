#include "main.h"
#include "tools.h"
#include "consumer.h"

void consumer(int consumer_id)
{
  int prod_occ;
  int prod_unocc;
  int prod_mem;
  int prod_read;
  int prod_offset;

  srand(time(NULL)+consumer_id);

  while(1)
  {
    int producer = rand() % 3;

/*    sleep(1);
    printf("Consumer %d | chose producer %c\n", consumer_id, producer+'A');*/

    switch (producer)
    {
      case PROD_A:
        prod_occ = A_OCC;
        prod_unocc = A_UNOCC;
        prod_mem = A_MEMORY;
        prod_read = A_READ;
        prod_offset = A_OFFSET;
        break;

      case PROD_B:
        prod_occ = B_OCC;
        prod_unocc = B_UNOCC;
        prod_mem = B_MEMORY;
        prod_read = B_READ;
        prod_offset = B_OFFSET;
        break;

      case PROD_C:
        prod_occ = C_OCC;
        prod_unocc = C_UNOCC;
        prod_mem = C_MEMORY;
        prod_read = C_READ;
        prod_offset = C_OFFSET;
        break;
      default:
        prod_occ = prod_unocc = prod_mem = prod_read = prod_offset = -1;
    }

    sem_down(sem_id, prod_occ);
    sem_down(sem_id, prod_mem);

/*  sleep(1);
    int read_item = memory[memory[prod_read]];
    printf("Consumer %d | pick item %d from Producer %c\n", consumer_id, read_item, producer+'A'); */
    int temp_index = memory[prod_read];
    temp_index = ( (temp_index + 1) % BUFFER_SIZE ) + prod_offset;

    sem_up(sem_id, prod_mem);
    if(producer == PROD_B)
      setParityFullB(1);
    sem_up(sem_id, prod_unocc);
  }
}

void create_cons(int id)
{
  int result = fork();
  if(result == 0)
  {
    consumer(id);
  }
}
