#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define _XOPEN_SOURCE 500

#define BUFFER_SIZE   9
#define MEMORY_SIZE   33
#define SEM_AMOUNT    11

#define PROD_A        0
#define PROD_B        1
#define PROD_C        2

/* SEMAPHORS */
#define A_UNOCC       0
#define A_OCC         1
#define A_MEMORY      2

#define C_UNOCC       3
#define C_OCC         4
#define C_MEMORY      5

#define B_UNOCC       6
#define B_OCC         7
#define B_MEMORY      8
#define B_ODD         9
#define B_EVEN_FULL   10

/* MEMORY STRUCTURE */
#define A_WRITE       9
#define A_READ        10
#define A_OFFSET      0

#define B_WRITE       20
#define B_READ        21
#define B_OFFSET      11

#define C_WRITE       31
#define C_READ        32
#define C_OFFSET      22

/* ADDITIONAL */
#define PROJ_ID       5861524

struct sembuf buf;
int sem_id;
int mem_id;
int *memory;

#endif
