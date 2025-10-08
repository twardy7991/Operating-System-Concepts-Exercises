#ifndef FCFS_H

#define FCFS_H
#include "base.h"

typedef struct FCFS {
    base super;
} FCFS;

void FCFS_construct(FCFS *self);

#endif