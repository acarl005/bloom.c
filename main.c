#include <stdio.h>
#include "bloom.h"

int main() {
    // create a BloomFilter with 10% false positives once 50 items are added
    BloomFilter *bf = bloom_filter_new(50, 0.1);

    // add a couple keys
    bloom_filter_add(bf, "food");
    bloom_filter_add(bf, "bar");

    // at this size, this should be very small
    printf("%.6f\n", bloom_filter_false_positive_prob(bf));

    // check if some keys are in the BloomFilter
    printf("%i\n", bloom_filter_might_contain(bf, "food"));
    printf("%i\n", bloom_filter_might_contain(bf, "sushi"));

    bloom_filter_free(bf);
    return 0;
}
