#ifndef CPU_H

#define CPU_H
#include "../task.h"

int create_history(void);
int run(Task *task, int time);
int close_history();

#endif