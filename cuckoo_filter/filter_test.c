#include <assert.h>
#include "cuckoo.h"
#include "hashutil.h"
#include <string.h>

int main() {
    struct cuckoo_filter *filter;
    filter = cuckoo_init(22, 4, 512, murmurhash, fingerprint);
    int inserts = filter->bucket_capacity * filter->bucket_size;

    for (int i = 0; i < inserts; i++) {
        char key[128];
        memset(key, 0, sizeof(char) * 128);
        sprintf(key, "keys-%d", i);
        printf("%s\n",key);
        cuckoo_insert(filter, key, strlen(key));
    }
    printf("填充率 %d ,total: %d, counts: %d evicated: %d\n",
           (cuckoo_count(filter) * 100) / inserts, inserts,
           cuckoo_count(filter), filter->evicate);

    int falsecount = 0;
    for (int i = inserts; i < inserts * 2; i++) {
        char key[128];
        memset(key, 0, sizeof(char) * 128);
        sprintf(key, "keys-%d", i);

        if (cuckoo_lookup(filter, key, strlen(key))) {
            falsecount++;
        }
    }
    printf("False positive %d\n", (falsecount * 100) / inserts);

    falsecount = 0;
    for (int i = 0; i < inserts; i++) {
        char key[128];
        memset(key, 0, sizeof(char) * 128);
        sprintf(key, "keys-%d", i);
        cuckoo_delete(filter, key, strlen(key));
    }

    for (int i = 0; i < inserts; i++) {
        char key[128];
        memset(key, 0, sizeof(char) * 128);
        sprintf(key, "keys-%d", i);
        if (cuckoo_lookup(filter, key, strlen(key)) == CUCKOO_OK) {
            falsecount++;
        }
    }
    printf("False positive after delete %d\n", (falsecount * 100) / inserts);

    return 0;
}
