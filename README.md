# Bloom Filter

A C implementation of a Bloom filter.

What is a Bloom filter? It's a probabilistic data structure for members in a set.
It is far more space efficient than a deterministic tree set or hash set.
The tradeoff is that sometimes when you check an element for membership, it sometimes says "true" (included in the set) when the element was never added, i.e. it *should* say "false".

More info coming soon.

## Usage

```c
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
    printf("%i\n", bloom_filter_might_contain(bf, "food")); // 1
    printf("%i\n", bloom_filter_might_contain(bf, "sushi")); // 0

    bloom_filter_free(bf);
    return 0;
}
```
