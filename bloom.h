#pragma once
#include <stdbool.h>

typedef struct BloomFilter {
    unsigned int capacity;
    unsigned int size;
    int hash_count;
    unsigned int* bit_array;
} BloomFilter;

/**
 * Creates a bloom filter on the heap. The optimal amount of memory and number of hash functions
 * is determined automatically. Provide the approximate number of items you'll store, and the
 * "false positive" probability at that size.
 * @param int items_count The anticipated number of items to store.
 * @param float fp_prob The probability of a false positive when the anticipated size is reached.
 * @return BloomFilter* Pointer to the allocated BloomFilter.
 */
BloomFilter* bloom_filter_new(long items_count, float fp_prob);

/**
 * Creates a bloom filter on the heap. This lets you manually choose the capacity and number of
 * hash functions.
 * @param int capacity The number of bits for storage.
 * @param int hash_count The probability of a false positive when the anticipated size is reached.
 * @return BloomFilter* Pointer to the allocated BloomFilter.
 */
BloomFilter* bloom_filter_with_capacity(unsigned int capacity, int hash_count);

/**
 * Adds a new key to the BloomFilter.
 * @param BloomFilter* bf The BloomFilter to add to.
 * @param char* key The string to add to the BloomFilter.
 */
void bloom_filter_add(BloomFilter* bf, char* key);

/**
 * Calculate the current false positive rate at this size. This will increase as elements are added.
 * @param BloomFilter* bf The BloomFilter for which to calculate the false positive rate.
 * @return float The false positive rate (fraction of the time a positive is returned from a query for a key not in the BloomFilter).
 */
float bloom_filter_false_positive_prob(BloomFilter* bf);

/**
 * Query if a key might be present in the BloomFilter.
 * @param BloomFilter* bf The BloomFilter to look for the key in.
 * @param char* key The string to check for.
 * @return bool If 0, the key is definitely not in the BloomFilter. If 1, it might be in it.
 */
bool bloom_filter_might_contain(BloomFilter* bf, char* key);

/**
 * Delete a BloomFilter.
 * @param BloomFilter* bf The BloomFilter to free.
 */
void bloom_filter_free(BloomFilter* bf);