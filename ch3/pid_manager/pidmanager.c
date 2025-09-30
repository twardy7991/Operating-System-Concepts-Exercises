#include <limits.h>    /* for CHAR_BIT */
#include <stdint.h>   /* for uint32_t */
#include <stdio.h>
#include <stdlib.h>

/* enum is better than #define as it enables type checking, could obey scope rules*/
// enum {BITS_PER_WORD = sizeof(uint64_t) * CHAR_BIT};
static const int BITS_PER_WORD = sizeof(uint64_t) * CHAR_BIT;

#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)
#define MIN_PID 300
#define MAX_PID 310
#define PID_SIZE ((((MAX_PID - MIN_PID) + BITS_PER_WORD - 1) / BITS_PER_WORD)) /* ((MAX_PID / BITS_PER_WORD) + 1) <- this could overallocate 1 word */

/* we set the pointer to pid array */
uint64_t *pid_ptr;

/* help function to check if pid is in required constaint */
int is_in_range(int n){
    if (!(0 <= n && n <= MAX_PID - MIN_PID)){
        printf("%i out of pid scope %i - %i\n", n, 0, MAX_PID - MIN_PID);
        return 0;
    }
    return 1;
}

/* function to get the n-th bit from array (MIN_PID + n) pid number*/
int get_bit(uint64_t *words, int n) {
    if (is_in_range(n)) {    
    uint64_t bit = words[WORD_OFFSET(n)] & (1ULL << BIT_OFFSET(n));
    return bit != 0; 
    }
    return -1;
}

/* function to set the n-th bit to 1 */
void set_bit(uint64_t *words, int n) { 
    if (is_in_range(n) && get_bit(pid_ptr, n) != 1) {
        words[WORD_OFFSET(n)] |= (1ULL << BIT_OFFSET(n));
        printf("bit setted: %i \n", n);
    } else {
    printf("could not set the bit: %i \n", n);
    }
}

/*function to set n-th bit to 0 */
void clear_bit(uint64_t *words, int n) {
    if (is_in_range(n)) {
        words[WORD_OFFSET(n)] &= ~(1ULL << BIT_OFFSET(n)); 
    }
}

/* initialize function for pid array */
int allocate_map(void){
    /* calloc allocates memory dynmically and set all bits to 0 (in oppose to malloc that initializes with garbage) */
    pid_ptr = calloc(PID_SIZE, sizeof(uint64_t));
    if (!pid_ptr){
        printf("malloc error \n"); return -1;
    }
    return 1;
}

/* function to deallocate the pid array from memory */
int deallocate_map(void){
    free(pid_ptr);
    return 1;
}

/* function to allocate a pid if available */
int allocate_pid(void){
    int c = MIN_PID;
    while (c < MAX_PID && get_bit(pid_ptr, c - MIN_PID) != 0){
        c += 1;
    }
    if (c < MAX_PID){
        set_bit(pid_ptr, c - MIN_PID);
        printf("pid allocated: %i \n", c);
        return 1;
    }
    printf("no pid available \n");
    return -1;
}

/* function to release a pid */
void release_pid(int pid){
    clear_bit(pid_ptr, pid - MIN_PID);
    printf("pid released %i \n", pid);
}

/* debug function to show how bit's values change */
void print_binary() {
    if (!pid_ptr) {printf("pid array not initialized \n"); return;}
    printf("------\n"); // total bits in the type
    for (int i = MAX_PID - MIN_PID - 1; i >= 0; i--) {
        printf("%i", get_bit(pid_ptr, i)); // extract each bit
    }
    printf("\n------\n");
}

/* main function that showcase allocation */
int main(void){
    printf("PID SIZE: %i \n", PID_SIZE);
    printf("BITS PER WORD: %i \n", BITS_PER_WORD);

    print_binary();
    allocate_map();
    print_binary();

    set_bit(pid_ptr, 1);

    print_binary();

    set_bit(pid_ptr, 2);
    set_bit(pid_ptr, 1);

    print_binary();

    allocate_pid();
    allocate_pid();

    print_binary();

    release_pid(302);

    print_binary();

    deallocate_map();
}

