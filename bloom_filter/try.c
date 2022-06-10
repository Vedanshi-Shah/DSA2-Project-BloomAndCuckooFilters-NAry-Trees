#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "bloom.h"

int main(void) {
    bloom_filter *filter = bloom_filter_new_default(1024);
    bloom_filter_put_str(filter, "abcd");
    //bloom_filter *filter2 = bloom_filter_new_default(1024);
    //bloom_filter_put_str(filter2, "wxyz");
    //bloom_filter *filter3 = bloom_filter_new_default(1024);
    //uint32_t a=(*filter->vect->mem|*filter2->vect->mem);
    //filter3->vect->mem=&a;
    //printf("%d\n",filter->vect->mem[3]);
    // printf("%d\n", bloom_filter_test_str(filter, "abc"));
    // printf("%d\n", bloom_filter_test_str(filter, "bcd"));
    // printf("%d\n", bloom_filter_test_str(filter, "0"));
    // printf("%d\n", bloom_filter_test_str(filter, "1"));
    // bloom_filter_put_str(filter, "2");
    //printf("%d\n", bloom_filter_test_str(filter3, "abcd"));
    
    return EXIT_SUCCESS;
}