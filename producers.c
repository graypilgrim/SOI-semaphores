#include "main.h"
#include "tools.h"
#include "producers.h"

void producerA()
{
  srand(time(NULL) + 'A');
  while(1)
  {
    sem_down(sem_id, A_UNOCC);
    sem_down(sem_id, B_ODD);
    sem_down(sem_id, A_MEMORY);

    int temp_index = memory[A_WRITE];
    memory[temp_index] = rand();
    memory[A_WRITE] = (memory[A_WRITE] + 1) % BUFFER_SIZE;

    sem_up(sem_id, A_MEMORY);
    sem_up(sem_id, B_ODD);
    sem_up(sem_id, A_OCC);
  }
}

void producerC()
{
  srand(time(NULL) + 'C');
  while(1)
  {
    sem_down(sem_id, C_UNOCC);
    sem_down(sem_id, B_EVEN_FULL);
    sem_down(sem_id, C_MEMORY);

    int temp_index = memory[C_WRITE];
    memory[temp_index] = rand();
    temp_index -= C_OFFSET;
    memory[C_WRITE] = ( (temp_index + 1) % BUFFER_SIZE ) + C_OFFSET;

    sem_up(sem_id, C_MEMORY);
    sem_up(sem_id, B_EVEN_FULL);
    sem_up(sem_id, C_OCC);
  }
}

void producerB()
{
  srand(time(NULL) + 'B');
  while(1)
  {
    sem_down(sem_id, B_UNOCC);
    semctl(sem_id, B_ODD, SETVAL,(int)0);
    semctl(sem_id, B_EVEN_FULL, SETVAL, (int)0);
    sem_down(sem_id, B_MEMORY);

    int temp_index = memory[B_WRITE];
    memory[temp_index] = rand();
    temp_index -= B_OFFSET;
    memory[B_WRITE] = ( (temp_index + 1) % BUFFER_SIZE ) + B_OFFSET;

    sem_up(sem_id, B_MEMORY);
    setParityFullB(0);
    sem_up(sem_id, B_OCC);
  }
}
