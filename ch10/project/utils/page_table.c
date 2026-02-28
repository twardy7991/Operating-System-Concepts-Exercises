#include <stdio.h>
#include "frames.h"
#include "tlb.h"

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

    int physical_page_number;
    if (get_tlb_entry(page_number, &physical_page_number) == 0){
        printf("page found in tlb! - ");
        printf("Physical memory %i ", (physical_page_number & 0xFF) * 256 + offset);
        return physical_page_number;
    }

    if (page_table[page_number] & 0x100){
        printf("page found ! - ");
        printf("Physical memory %i ", (page_table[page_number] & 0xFF) * 256 + offset);
        create_tlb_entry(page_number, page_table[page_number]);
        return get_physical_frame(page_table[page_number] & 0xFF, offset);
    }

    for (int i = 0; i < PAGE_TABLE_SIZE; i++){
        if (~(page_table[i] & 0x100)){
            char physical_page = allocate_page(page_number, offset);
            create_tlb_entry(page_number, physical_page);
            return physical_page;
            break;
        }
    }
    return -1;
}

