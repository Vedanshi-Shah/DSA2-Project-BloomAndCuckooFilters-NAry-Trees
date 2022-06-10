#include "hashutil.h"

uint32_t murmurhash(const char *buf, size_t len) {
    uint32_t seed = 0;
    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    uint32_t h = seed ^ len;
    const unsigned char *data = (const unsigned char *)buf;

    while (len >= 4) {
        unsigned int k = *(unsigned int *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

uint32_t bkdr(const char *key, size_t len) {
    uint64_t i;
    uint32_t seed = 131;
    int32_t hash = 0;

    for (i = 0; i < len; i++) {
        hash = (hash * seed) + key[i];
    }

    return hash >= 0 ? hash : -1 * hash;
}

uint8_t fingerprint(const char *key, size_t len) {
    return bkdr(key, len) % 255 + 1;
}
