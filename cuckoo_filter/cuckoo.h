#ifndef __CUCKOO_H__
#define __CUCKOO_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t (*hash_func_t)(const char *, size_t);
typedef uint8_t (*fp_func_t)(const char *, size_t);

typedef struct cuckoo_filter {
    uint8_t *bucket;
    int max_kicks;
    int counts;
    int bucket_capacity;
    int bucket_size;
    int poweroftwo;
    int evicate;
    int evicate_fp;
    int evicate_index;
    hash_func_t hash;
    fp_func_t fp;
}cuckoo_filter;

struct cuckoo_filter *cuckoo_init(int powerof2, int bucket_size, int kicks,
                                  hash_func_t hash, fp_func_t fp);
void cuckoo_deinit(struct cuckoo_filter *);
int cuckoo_insert(struct cuckoo_filter *filter, const char *key, size_t len);
int cuckoo_lookup(struct cuckoo_filter *filter, const char *key, size_t len);
int cuckoo_delete(struct cuckoo_filter *filter, const char *key, size_t len);
int cuckoo_count(struct cuckoo_filter *filter);
int cuckoo_rehash(struct cuckoo_filter *filter);

#define CUCKOO_OK 1
#define CUCKOO_ERR 0
#define CUCKOO_NEXIST -1

#endif
