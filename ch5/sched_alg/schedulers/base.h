#ifndef BASE_H

#define BASE_H

#include "../task.h"

/* struct that is a base/super for every scheduling algorithm,
specifies the functions that have to be defined, 
this approach enables inheritance and, what is more important,
polymorphzm, that reduces boilerplate code and is easier to maintain */

typedef struct base {
        int (*build_queue)(struct base *self, Task* tasks, int n_task);
        int (*pick_run)(struct base *self);
        int (*del_queue)(struct base *self);
    } base;

#endif 