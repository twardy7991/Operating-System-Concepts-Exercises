#include <stdlib.h>
#include <stdio.h>
#include "reader.h"

int main(int argc, char *argv[]){

    printf("i am working\n");

    if (argc < 2) {
        printf("Użycie: %s <liczba>\n", argv[0]);
        return 1;
    }

    char *endptr;

    for (int i = 1; i < argc; i++){
        char value;
        long int address = strtol(argv[i], &endptr, 10);
        printf("address: %li\n", address);
        value = read_offset(address);
        printf("physical address: %li, Value: %i\n", address, value);
    }
    return 0;
}

