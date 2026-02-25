#include <stdio.h>
#include <stdlib.h>

char *read_offset(long int offset){

    char *buffer =  (char *)malloc(256);
    const char *filename = "/home/twardy/projects/c/ch10/project/utils/BACKING_STORE.bin";

    FILE *backing_store;
    backing_store = fopen(filename, "rb");

    if (backing_store == NULL){
        printf("file not found\n");
        free(buffer);
        return NULL;
    }

    fseek(backing_store, offset * 256, SEEK_SET);
    fread(buffer, sizeof(char), 256, backing_store);
    fclose(backing_store);

    return buffer;
}

// char *read_addresses(){

//     char filename = "/home/twardy/projects/c/ch10/project/utils/addresses.txt";


// }
