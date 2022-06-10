#ifndef __HASHUTIL_H__
#define __HASHUTIL_H__

#include <stdint.h>
#include <sys/types.h>

uint32_t murmurhash(const char *buf, size_t len);
uint8_t fingerprint(const char *key,size_t len);
uint32_t bkdr(const char *key, size_t len);
#endif
