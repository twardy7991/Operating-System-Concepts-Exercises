#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils/page_table.h"

size_t str_len(char *string){
    int c = 0;

    while (1){
        if (string[c] == '\0'){
            return (size_t)c;
        }
        c += 1;
    } 
}

void print_binary(unsigned int value){
    int bits = 8 * sizeof(value);
    for (int i = bits - 1; i>=0; i--){
        printf("%u", (value >> i) & 1);
    }
    printf("\n"); 
}
     
int convert_to_int(char *string_num, long int *number, size_t size){
    int num = 0;

    for (int i = 0; i < size; i++){
        num += ((string_num[i] - '0') * (int)pow((double)10, (double)((int)size - i - 1)));
    }

    *number = num;
    return 0;
}

int main(int argc, char *argv[]){

    long int addresses[argc - 1];
    int page_number;
    int offset;

    for (int i = 0; i < argc - 1; i++){
        size_t size = str_len(argv[i + 1]);
        convert_to_int(argv[i + 1], &addresses[i], size);

        // print_binary((unsigned int)addresses[i]);
        // print_binary((unsigned int)0xFFFF);
        // print_binary((unsigned int)addresses[i] & 0xFFFF);
        // print_binary((unsigned int)(addresses[i] & 0xFFF0));
        // print_binary((unsigned int)(addresses[i] & 0xFF0F));

        //printf("number %li\n", addresses[i]);
        //printf("page number of %li = %i\n", addresses[i], (int)(addresses[i] & 0xFF00) >> 8);
        //printf("offset of %li = %i\n", addresses[i], (int)(addresses[i] & 0x00FF));

        page_number = (addresses[i] & 0xFF00) >> 8;
        offset = (addresses[i] & 0x00FF);

        char value;
        printf("Virtual address: %li ", addresses[i]);

        value = get_frame(page_number, offset);

        printf("Value: %i \n" , value);
    }

    return 0;
}