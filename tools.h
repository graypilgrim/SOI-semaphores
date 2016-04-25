#ifndef TOOLS_H
#define TOOLS_H

int sem_up(int sem_id, int sem_num);
int sem_down(int sem_id, int sem_num);
int init();
void create_prod(void (*function)());
void setParityFullB(int actual);
void printBars();

#endif
