#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "murmurhash.h"
#include "bloom.h"
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
// the number of bits in a word
#define WORD_BITS (8 * sizeof(unsigned int))


// bit array helpers
// -----------------
// The bit_array member of BloomFilter could be a simple bool[] with each element being individually
// addressable by an index. However, that wastes memory, as the elements are aligned to memory addresses
// which are not 1 bit apart. To avoid that wasteful "padding", I will pack the bits together so multiple
// elements fit into one address. This involves doing some bit manipulation to get/set individuals.
// Note that it is also slower to do this compared to a traditional bool[].
static void set_index(unsigned int* bit_array, size_t i) {
    bit_array[i / WORD_BITS] |= (1 << (i % WORD_BITS));
}

static bool get_index(unsigned int* bit_array, size_t i) {
    return bit_array[i / WORD_BITS] & (1 << (i % WORD_BITS));
}

BloomFilter* bloom_filter_new(long items_count, float fp_prob) {
    unsigned int capacity = -items_count * log(fp_prob) / pow(log(2), 2);
    int hash_count = log(2) * capacity / items_count;
    return bloom_filter_with_capacity(capacity, hash_count);
}

BloomFilter* bloom_filter_with_capacity(unsigned int capacity, int hash_count) {
    BloomFilter* bf = malloc(sizeof(BloomFilter));
    if (bf == NULL) {
        return NULL;
    }
    bf->capacity = capacity;
    bf->bit_array = calloc(capacity / WORD_BITS + 1, sizeof(unsigned int));
    bf->size = 0;
    bf->hash_count = MAX(hash_count, 1);
    return bf;
}

void bloom_filter_add(BloomFilter* bf, char* key) {
    for (int i = 0; i < bf->hash_count; i++) {
        size_t ind = murmurhash(key, strlen(key), i) % bf->capacity;
        set_index(bf->bit_array, ind);
    }
    bf->size++;
}

static bool any_zero_bits(BloomFilter* bf, char* key) {
    bool any_zeros = false;
    for (int i = 0; i < bf->hash_count; i++) {
        size_t ind = murmurhash(key, strlen(key), i) % bf->capacity;
        any_zeros = any_zeros || get_index(bf->bit_array, ind) == 0;
    }
    return any_zeros;
}

bool bloom_filter_might_contain(BloomFilter* bf, char* key) {
    return !any_zero_bits(bf, key);
}

float bloom_filter_false_positive_prob(BloomFilter* bf) {
    return pow(1.0 - pow(1.0 - 1.0 / bf->capacity, (double)bf->hash_count * bf->size), bf->hash_count);
}

void bloom_filter_free(BloomFilter* bf) {
    free(bf->bit_array);
    free(bf);
}
