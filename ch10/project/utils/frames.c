#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include <string.h>

#define PHYSICAL_MEMORY_PAGE_SIZE 256
#define PHYSICAL_MEMORY_ROWS 256

char physical_memory[PHYSICAL_MEMORY_PAGE_SIZE + 1][PHYSICAL_MEMORY_ROWS];
int free_frames[PHYSICAL_MEMORY_ROWS];
int free_count = PHYSICAL_MEMORY_ROWS;

char get_physical_frame(int frame_number, int offset){
    return physical_memory[frame_number][offset];
}

int allocate_physical_frame(int virtual_frame_number, char **value){

    int i;
    for (i = 0; i < PHYSICAL_MEMORY_ROWS; i++){
        if (free_frames[i] == 0){
            break;
        }
    }

    if (i >= PHYSICAL_MEMORY_ROWS){
        printf("Error: No free frames available\n");
        return -1;
    }

    free_frames[i] = 1;
    free_count = free_count - 1;

    *value = read_offset(virtual_frame_number);

    memcpy(physical_memory[i], *value, 256);
    // int j;
    // for (j = 0; j < 256; j++){
    //     physical_memory[i][j] = value[j];
    // }

    return i;
}