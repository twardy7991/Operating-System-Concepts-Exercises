#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>

static int lock = 0;

int waiting[4];

/* thats a pseudo code for atomic_compare_exchange_strong */
// int compare_and_swap(int *value, int *expected, int new_value) {
//     int old = *value;
//     if (*value == *expected) {
//         *value = new_value;
//         return 1; // success
//     } else {
//         *expected = old; // update expected
//         return 0; // failure
//     }
// }

int get_waiting(int i){
    return atomic_load(&waiting[i]);
}


void set_waiting_true(int i){
    int expected = 0;
    int desired = 1;

    while (!atomic_compare_exchange_strong(&waiting[i], &expected, desired)){
    }
}

void set_waiting_false(int i){
    int expected = 1;
    int desired = 0;

    while (!atomic_compare_exchange_strong(&waiting[i], &expected, desired)){
    }
}

void acquire(int i){
    set_waiting_true(i);

    int expected = 0;
    int desired = 1;
    int val = 0;
    while (get_waiting(i) && val == 0){
        val = atomic_compare_exchange_strong(&lock, &expected, desired);
        expected = 0;
    }
    set_waiting_false(i);
}

void release(int i){

    int n = 4;
    int j = (i + 1) % n;

    while ((j != i) && !get_waiting(j)){
        j = (j + 1) % n;
    }

    if (j == i){
        int expected = 1;
        int desired = 0; 

        atomic_compare_exchange_strong(&lock, &expected, desired);
    } else {
        set_waiting_false(j);
    }
}