#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "murmurhash.h"
#include "bloom.h"
#define MAX(a,b) (((a)>(b))?(a):(b))

BloomFilter* bloom_filter_new(long items_count, float fp_prob) {
    long capacity = -items_count * log(fp_prob) / pow(log(2), 2);
    int hash_count = log(2) * capacity / items_count;
    return bloom_filter_with_capacity(capacity, hash_count);
}

BloomFilter* bloom_filter_with_capacity(long capacity, int hash_count) {
    BloomFilter* bf = malloc(sizeof(BloomFilter));
    bf->capacity = capacity;
    bf->bit_array = calloc(capacity, sizeof(bool));
    bf->size = 0;
    bf->hash_count = MAX(hash_count, 1);
    return bf;
}

void bloom_filter_add(BloomFilter* bf, char* key) {
    for (int i = 0; i < bf->hash_count; i++) {
        size_t ind = murmurhash(key, strlen(key), i) % bf->capacity;
        bf->bit_array[ind] = 1;
    }
    bf->size++;
}

static bool any_zero_bits(BloomFilter* bf, char* key) {
    bool any_zeros = false;
    for (int i = 0; i < bf->hash_count; i++) {
        size_t ind = murmurhash(key, strlen(key), i) % bf->capacity;
        any_zeros = any_zeros || bf->bit_array[ind] == 0;
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