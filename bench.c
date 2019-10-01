#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"

int main() {
    BloomFilter *bf = bloom_filter_new(10000000, 0.01);
    printf("%u\n", bf->capacity);

    srand(1337); // seed random number generation
    char key[17]; // create a buffer for randomly generated string keys
    for (int i = 0; i < 10000000; i++) {
        sprintf(key, "%08x", rand()); // write the first 8 digits (1 4-byte int is only 8 hex digits)
        sprintf(key + 8, "%08x", rand()); // write the second 8 digits
        bloom_filter_add(bf, key);
        bloom_filter_might_contain(bf, key);
    }

    bloom_filter_free(bf);
    return 0;
}
