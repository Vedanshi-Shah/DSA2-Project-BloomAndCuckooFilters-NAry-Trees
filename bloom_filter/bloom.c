#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>
#include "bloom.h"
#include "hashf.h"

bloom_filter *bloom_filter_new(size_t size, size_t num_functions, ...) {
    va_list argp;
    bloom_filter *filter = malloc(sizeof(*filter));
    if (NULL==filter) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    filter->num_items = 0;
    filter->vect = bit_vect_new(size);
    filter->num_functions = num_functions;
    filter->hash_functions = malloc(sizeof(hash32_func)*num_functions);
    if (NULL==filter->hash_functions) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);    
    }
    va_start(argp, num_functions);
    for(unsigned i = 0; i < num_functions; i++) {
        filter->hash_functions[i] = va_arg(argp, hash32_func);
    }
    va_end(argp);
    return filter;
}

bloom_filter *bloom_filter_new_default(size_t size) {
    return bloom_filter_new(size, 2, djb2, sdbm);
} 

void bloom_filter_free(bloom_filter *filter) {
    bit_vect_free(filter->vect);
    free(filter->hash_functions);
    free(filter);
}

void bloom_filter_put(bloom_filter *filter, const void *data, size_t length){
    for(unsigned i = 0; i < filter->num_functions; i++) {
        uint32_t cur_hash = filter->hash_functions[i](data, length);
        bit_vect_set1(filter->vect, cur_hash % filter->vect->size);
        filter->num_items++;
    }
}

void bloom_filter_put_str(bloom_filter *filter, const char *str) {
    bloom_filter_put(filter, str, strlen(str));
}


bool bloom_filter_test(bloom_filter *filter, const void *data, size_t lentgth) {
    for(unsigned i = 0; i < filter->num_functions; i++) {
        uint32_t cur_hash = filter->hash_functions[i](data, lentgth);
        if (!bit_vect_get(filter->vect, cur_hash % filter->vect->size)) {
            return false;
        }
    }
    return true;
}

bool bloom_filter_test_str(bloom_filter *filter, const char *str) {
    return bloom_filter_test(filter, str, strlen(str));
}
