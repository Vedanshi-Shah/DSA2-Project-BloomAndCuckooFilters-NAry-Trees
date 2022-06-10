#include "cuckoo.h"
#include <assert.h>
#include <stdio.h>
#include "hashutil.h"
#include <string.h>

static uint32_t lookup_entry(struct cuckoo_filter *filter, uint32_t bindex) {
    int bucket_size = filter->bucket_size;
    for (uint32_t i = 0; i < bucket_size; i++) {
        if (!filter->bucket[bindex * bucket_size + i])
            return bindex * bucket_size + i;
    }

    return CUCKOO_NEXIST;
}
int cuckoo_random(int max) { 
    return rand() % max; 
}
static int lookup_entry_fp(struct cuckoo_filter *filter, int bindex,
                           uint8_t fp) {
    int bucket_size = filter->bucket_size;

    for (int i = 0; i < bucket_size; i++) {
        if (filter->bucket[bindex * bucket_size + i] == fp)
            return bindex * bucket_size + i;
    }

    return CUCKOO_NEXIST;
}

static void try_reinsert_evicate(struct cuckoo_filter *filter) {
    filter->evicate = 0;

    uint32_t i = filter->evicate_index;
    uint8_t fp = filter->evicate_fp;
    filter->evicate_index = 0;
    filter->evicate_fp = 0;

    uint32_t mask = (1 << filter->poweroftwo) - 1;

    uint32_t entry;
    for (int n = 0; n < filter->max_kicks; n++) {
        entry = i * filter->bucket_size + cuckoo_random(filter->bucket_size);
        uint8_t pick = filter->bucket[entry];
        filter->bucket[entry] = fp;
        fp = pick;

        i = (filter->hash((char *)&fp, sizeof(uint8_t)) ^ i) & mask;
        if ((entry = lookup_entry(filter, i)) != CUCKOO_NEXIST) {
            filter->bucket[entry] = fp;
            return;
        }
    }

    filter->evicate = 1;
    filter->evicate_index = i;
    filter->evicate_fp = fp;
}

struct cuckoo_filter *cuckoo_init(int poweroftwo, int bucket_size, int kicks,
                                  hash_func_t hash, fp_func_t fp) {
    struct cuckoo_filter *filter = malloc(sizeof(struct cuckoo_filter));
    filter->max_kicks = kicks;
    filter->counts = 0;
    filter->bucket_capacity = 1 << poweroftwo;
    filter->bucket_size = bucket_size;
    filter->poweroftwo = poweroftwo;
    filter->evicate = 0;
    filter->evicate_fp = 0;
    filter->evicate_index = 0;
    filter->hash = hash;
    filter->fp = fp;
    filter->bucket = malloc(sizeof(uint8_t) * bucket_size * filter->bucket_capacity);
    memset(filter->bucket, 0x0, bucket_size * filter->bucket_capacity);

    return filter;
}

void cuckoo_deinit(struct cuckoo_filter *filter) {
    free(filter->bucket);
    free(filter);
}

static int x = 0;

int cuckoo_insert(struct cuckoo_filter *filter, const char *key, size_t len) {
    if (filter->evicate)
        return CUCKOO_ERR;
    uint8_t fp = filter->fp(key, len);
    uint32_t mask = (1 << filter->poweroftwo) - 1;

    uint32_t i1 = filter->hash(key, len) & mask;
    uint32_t i2 = (filter->hash((char *)&fp, sizeof(uint8_t)) ^ i1) & mask;
    uint32_t i;
    uint32_t entry = 0;
    if ((entry = lookup_entry(filter, i1)) != CUCKOO_NEXIST) {
        filter->bucket[entry] = fp;
        //printf("%d\n",entry);
        filter->counts++;
        return CUCKOO_OK;
    } else if ((entry = lookup_entry(filter, i2)) != CUCKOO_NEXIST) {
        filter->bucket[entry] = fp;
        //printf("%d\n",entry);
        filter->counts++;
        return CUCKOO_OK;
    } else {
        i = (cuckoo_random(2) == 0) ? i1 : i2;

        for (int n = 0; n < filter->max_kicks; n++) {
            entry =
                i * filter->bucket_size + cuckoo_random(filter->bucket_size);
            uint8_t pick = filter->bucket[entry];
            filter->bucket[entry] = fp;
            fp = pick;

            i = (filter->hash((char *)&fp, sizeof(uint8_t)) ^ i) & mask;
            if ((entry = lookup_entry(filter, i)) != CUCKOO_NEXIST) {
                filter->bucket[entry] = fp;
                //printf("%d\n",entry);
                filter->counts++;
                return CUCKOO_OK;
            }
        }
    }

    filter->evicate = 1;
    filter->evicate_index = i;
    filter->evicate_fp = fp;
    return CUCKOO_OK;
}

int cuckoo_lookup(struct cuckoo_filter *filter, const char *key, size_t len) {
    uint8_t fp = filter->fp(key, len);
    uint32_t mask = (1 << filter->poweroftwo) - 1;

    uint32_t i1 = filter->hash(key, len) & mask;
    uint32_t i2 = (filter->hash((char *)&fp, sizeof(uint8_t)) ^ i1) & mask;

    if (filter->evicate && fp == filter->evicate_fp &&
        (i1 == filter->evicate_index || i2 == filter->evicate_index)) {
        return CUCKOO_OK;
    }

    if (lookup_entry_fp(filter, i1, fp) != CUCKOO_NEXIST ||
        lookup_entry_fp(filter, i2, fp) != CUCKOO_NEXIST) {
        return CUCKOO_OK;
    }

    return CUCKOO_ERR;
}

int cuckoo_count(struct cuckoo_filter *filter) { return filter->counts; }

int cuckoo_delete(struct cuckoo_filter *filter, const char *key, size_t len) {
    uint8_t fp = filter->fp(key, len);
    uint32_t mask = (1 << filter->poweroftwo) - 1;
    uint32_t i1 = filter->hash(key, len) & mask;
    uint32_t i2 = (filter->hash((char *)&fp, sizeof(uint8_t)) ^ i1) & mask;
    uint32_t entry = 0;

    if ((entry = lookup_entry_fp(filter, i1, fp)) != CUCKOO_NEXIST ||
        (entry = lookup_entry_fp(filter, i2, fp)) != CUCKOO_NEXIST) {
        filter->bucket[entry] = 0;
        filter->counts--;
        if (filter->evicate)
            try_reinsert_evicate(filter);
        return CUCKOO_OK;
    }

    return CUCKOO_ERR;
}

