//
// use for debugging of failed tests
//

#include "../include/arithmetic.h"
#include "../include/number.h"
#include "../include/numutils.h"
#include "../include/picture.h"
#include "../include/picutils.h"
#include <stdio.h>


int main(){

    for(int i = 0; i < 127; ++i){
        char c[3] = { 'Q', i, 'F' };
        char mask[3] = { 'X', '9', 'X' };
        bstd_Picture* pic = bstd_picutils_of(c, mask, 3);

        char* cstrval = bstd_picutils_to_cstr(pic);
        printf("%s\n", cstrval);

    }

    for(int i = 'A'; i <= 'Z'; ++i){
        char c[3] = { i, 1, i };
        char mask[3] = { 'X', '9', 'X' };
        bstd_Picture* pic = bstd_picutils_of(c, mask, 3);

        char* cstrval = bstd_picutils_to_cstr(pic);
        printf("%s\n", cstrval);
    }

    for(int i = 'a'; i <= 'z'; ++i){
        char c[3] = { i, 1, i };
        char mask[3] = { 'X', '9', 'X' };
        bstd_Picture* pic = bstd_picutils_of(c, mask, 3);

        char* cstrval = bstd_picutils_to_cstr(pic);
        printf("%s\n", cstrval);

    }

    return 0;
};