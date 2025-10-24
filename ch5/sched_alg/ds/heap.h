#ifndef HEAP_H

#define HEAP_H
#include "../task.h"

Task *heapify(Task *list, int list_len);
Task *heap_extract(Task *heap);

#endif 