#ifndef TLB_H

#define TLB_H

int get_tlb_entry(int virtual_page_number, int *physical_page_number);
int create_tlb_entry(int virtual_page_number, int physical_page_number);

#endif