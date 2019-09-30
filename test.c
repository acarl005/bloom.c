#include <stdio.h>
#include "tap.h"
#include "bloom.h"

int main() {
    plan(3);
    BloomFilter *bf = bloom_filter_new(100, 0.1);

    cmp_ok(bloom_filter_false_positive_prob(bf), "==", 0);
    bloom_filter_add(bf, "food");
    bloom_filter_add(bf, "bar");
    cmp_ok(bloom_filter_might_contain(bf, "food"), "==", 1);
    cmp_ok(bloom_filter_might_contain(bf, "sushi"), "==", 0);

    bloom_filter_free(bf);
    return 0;
}