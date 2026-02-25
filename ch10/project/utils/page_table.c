#include <stdio.h>
#include "frames.h"


#define PAGE_TABLE_SIZE 256

int page_table[PAGE_TABLE_SIZE];

char allocate_page(int virtual_frame_number, int offset){

    char *frame;

    int physical_frame_number;

    physical_frame_number = allocate_physical_frame(virtual_frame_number, &frame);
    printf("Physical memory %i ", physical_frame_number * 256 + offset);

    page_table[virtual_frame_number] = physical_frame_number;

    page_table[virtual_frame_number] = physical_frame_number ^ 0x100;
    
    char value = frame[offset];

    return value;
}

char get_frame(int page_number, int offset){

    if (page_table[page_number] & 0x100){
        printf("page found ! - ");
        printf("Physical memory %i ", (page_table[page_number] & 0xFF) * 256 + offset);
        return get_physical_frame(page_table[page_number] & 0xFF, offset);
    }

    for (int i = 0; i < PAGE_TABLE_SIZE; i++){
        if (~(page_table[i] & 0x100)){
            return allocate_page(page_number, offset);
            break;
        }
    }
    return -1;
}

