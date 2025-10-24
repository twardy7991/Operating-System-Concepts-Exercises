/* MODULE THAT RETURNS THE DJB2 HASH FOR STRING PROVIDED AS PRORAM ARG
USED FOR MANUAL CALCULATION OF THE VALUES FOR SWITCH CASE IN SCHEDULE MODULE */

#include <stdio.h>
#include "hash.h"

int main(int argc, char *argv [])
{
    if (argc < 2){
        fprintf(stderr, "too few arguments");
        return 1;
    }

    for (int i = 1; i < argc; i++){
        unsigned long hashed = hash_djb2((unsigned char *)argv[i]);
        printf("hash for %s = %lu \n", argv[i], hashed);
    }

    return 0;
}