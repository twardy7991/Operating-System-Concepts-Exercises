// MODULE THAT IMPLEMENTS A MIN-HEAP DATA STRUCTURE BASED ON CPU_BURST VALUES 

#include "../task.h" 
#include <stdlib.h>
#include <stdio.h>

Task *heap;
int len_heap;

int parent(int i){
    return (int) (i / 2);
}

int left(int i){
    return 2 * i + 1;
}

int right(int i){
    return 2 * i + 2;
}

// swap nodes on positions i and j
void swap(int i, int j){
    Task hold = heap[i]; 
    heap[i] = heap[j];
    heap[j] = hold;
    return;
}

// satisfiy min-heap property between i-th node and its childs (if they exist)
void min_heapify(int i){
    int largest = 0;
    int l = left(i);
    int r = right(i);

    if (l <= len_heap && heap[l].cpu_burst < heap[i].cpu_burst){
        largest = l;
    } else {
        largest = i;
    }

    if (r <= len_heap && heap[r].cpu_burst < heap[largest].cpu_burst){
        largest = r;        
    }

    // for (int i = 0; i < 8; i++){
    //   printf("%i ," , heap[i].cpu_burst);    
    // }

    // printf("parent %i, l : %i, r : %i", i, l, r);  
    
    // printf("\n");

    if (largest != i){
        swap(i, largest);
        min_heapify(largest);
    }
    return;
}

// initialize the heap from a provided array of tasks
Task *heapify(Task *list, int list_len)
{
    len_heap = list_len - 1;
    heap = malloc(sizeof(list) * list_len);
    heap = list;
    for (int i = ((int)((list_len - 2) / 2)) ; i >= 0; i--){
        min_heapify(i);
    }
    return &heap[0];
}

// extract a task from on top of the heap and restore min heap property
Task *heap_extract(Task *heap)
{
    if (len_heap < 0){
        printf("heap is empty\n");
        return NULL;
    }
    Task* min = malloc(sizeof(Task));

    *min = heap[0];
    swap(0, len_heap);
    len_heap -= 1;

    min_heapify(0);

    // for (int i = 0; i < len_heap - 1; i++){
    //   printf("%i ," , heap[i].cpu_burst);    
    // }
    // printf("\n");

    return min;
}   