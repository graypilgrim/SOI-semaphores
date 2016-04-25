#include "main.h"
#include "tools.h"

int sem_up(int sem_id, int sem_num)
{
  buf.sem_num = sem_num;
  buf.sem_op = 1;
  buf.sem_flg = 0;

  return semop(sem_id, &buf, 1);
}

int sem_down(int sem_id, int sem_num)
{
  buf.sem_num = sem_num;
  buf.sem_op = -1;
  buf.sem_flg = 0;

  return semop(sem_id, &buf, 1);
}

int init()
{

  mem_id = shmget(PROJ_ID, 3*(BUFFER_SIZE+2)*sizeof(int), IPC_CREAT|0600);
  if(mem_id == -1)
  {
    perror("shmget");
    return -1;
  }

  memory = (int*)shmat(mem_id, NULL, 0);
  if(memory == NULL)
  {
    perror("shmat");
    return -1;
  }

  sem_id = semget(PROJ_ID, SEM_AMOUNT, IPC_CREAT|0600);
  if(sem_id == -1)
  {
    perror("semget");
    return -1;
  }

/* ============== PRODUCER A =================*/
  if( semctl(sem_id, A_UNOCC, SETVAL,(int)BUFFER_SIZE) == -1 )
  {
    perror("setting value for sem A_UNOCC");
    return -1;
  }

  if( semctl(sem_id, A_OCC, SETVAL,(int)0) == -1 )
  {
    perror("setting value for sem A_OCC");
    return -1;
  }

  if( semctl(sem_id, A_MEMORY, SETVAL,(int)1) == -1 )
  {
    perror("setting value for sem A_MEMORY");
    return -1;
  }

  memory[A_READ] = memory[A_WRITE] = 0;

/* ============== PRODUCER C =================*/
  if( semctl(sem_id, C_UNOCC, SETVAL,(int)BUFFER_SIZE) == -1 )
  {
    perror("setting value for sem C_UNOCC");
    return -1;
  }

  if( semctl(sem_id, C_OCC, SETVAL,(int)0) == -1 )
  {
    perror("setting value for sem C_OCC");
    return -1;
  }

  if( semctl(sem_id, C_MEMORY, SETVAL,(int)1) == -1 )
  {
    perror("setting value for sem C_MEMORY");
    return -1;
  }

  memory[C_READ] = memory[C_WRITE] = C_OFFSET;

  /* ============== PRODUCER B =================*/
  if( semctl(sem_id, B_UNOCC, SETVAL,(int)BUFFER_SIZE) == -1 )
  {
    perror("setting value for sem B_UNOCC");
    return -1;
  }

  if( semctl(sem_id, B_OCC, SETVAL,(int)0) == -1 )
  {
    perror("setting value for sem B_OCC");
    return -1;
  }

  if( semctl(sem_id, B_MEMORY, SETVAL,(int)1) == -1 )
  {
    perror("setting value for sem B_MEMORY");
    return -1;
  }

  if( semctl(sem_id, B_ODD, SETVAL,(int)0) == -1 )
  {
    perror("setting value for sem B_ODD");
    return -1;
  }

  if( semctl(sem_id, B_EVEN_FULL, SETVAL,(int)1) == -1 )
  {
    perror("setting value for sem B_EVEN");
    return -1;
  }

  memory[B_READ] = memory[B_WRITE] = B_OFFSET;

  return 0;
}

void create_prod(void (*function)())
{
  int result = fork();
  if(result == 0)
  {
    function();
  }
}

void setParityFullB(int actual)
{
  int x = (actual == 1) ? 0 : 1;

  int occupied = semctl(sem_id, B_OCC, GETVAL, 0) + x;

  int occ_parity = (occupied) % 2;

  if(occ_parity == 0 || occupied == BUFFER_SIZE)
    sem_up(sem_id, B_EVEN_FULL);

  if(occ_parity != 0)
    sem_up(sem_id, B_ODD);
}

void printBars()
{
  int i;
  int size;

  size = semctl(sem_id, A_OCC, GETVAL, 0);
  printf("A: ");
  for(i = size; i >= 0; --i)
    printf("#");
  printf("\n");

  size = semctl(sem_id, B_OCC, GETVAL, 0);
  printf("B: ");
  for(i = size; i >= 0; --i)
    printf("#");
  printf("\n");

  size = semctl(sem_id, C_OCC, GETVAL, 0);
  printf("C: ");
  for(i = size; i > 0; --i)
    printf("#");
  printf("\n\n");
}
