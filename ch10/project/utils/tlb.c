#include <stdio.h>


#define TLB_SIZE 16

struct tlb_entry {
    int address;
    char is_valid;
    char counter;
};

int lowest_counter;
int lowest_counter_entry;
struct tlb_entry tlb[16];

int get_tlb_entry(int virtual_page_number, int *physical_page_number){
    lowest_counter = tlb[0].counter;
    lowest_counter_entry = 0;

    for (int i = 0; i < TLB_SIZE;  i++){
        if (lowest_counter > tlb[i].counter){
            lowest_counter = tlb[i].counter;
            lowest_counter_entry = i;
        }

        int tlb_entry_virtual_page_number = (int)(tlb[i].address >> 8);

        if ((tlb[i].is_valid & 0x1) & (virtual_page_number == tlb_entry_virtual_page_number)){
            tlb[i].counter++; 
            int tlb_address =(int) tlb[i].address; 
            *physical_page_number= tlb_address;
            return 0;
        }
    }
    return -1;
}

int create_tlb_entry(int virtual_page_number, int physical_page_number){
    printf("Creating tlb entry, ");

    struct tlb_entry *new_tlb_entry = &tlb[lowest_counter_entry];

    new_tlb_entry->address = (virtual_page_number << 8) + (physical_page_number & 0x00FF);
    new_tlb_entry->is_valid = 1;
    new_tlb_entry->counter = 1;

    return 0;
}
