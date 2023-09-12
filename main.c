#include "include/numutils.h"
#include <memory.h>
#include <malloc.h>
#include <stdio.h>

int main(){
// used for debugging

    int s = sizeof(bstd_number);
    bstd_number* n = malloc(s);
    (*n) = (bstd_number){
        .value = 1,
        .scale = 2,
        .length = 3,
        .isSigned = true,
        .positive = true,
    };

    char* c = malloc(s);
    memcpy(c, n, s);
    printf("size: %d\r\n", s);
    for ( int i = 0; i < s; ++i) {
        printf("%d\t%d\r\n", i, (int)c[i]);
    }

    printf("offsets\r\n");
    printf("%lu\r\n", offsetof(bstd_number , value));
    printf("%lu\r\n", offsetof(bstd_number , scale));
    printf("%lu\r\n", offsetof(bstd_number , length));
    printf("%lu\r\n", offsetof(bstd_number , isSigned));
    printf("%lu\r\n", offsetof(bstd_number , positive));

}