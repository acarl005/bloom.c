# Bloom Filter

A C implementation of a Bloom filter.

### What is a Bloom filter?

It's a probabilistic data structure for members in a set.
It is far more space efficient than a deterministic tree set or hash set.
The trade-off is that sometimes when you check an element for membership, it sometimes says "true" (included in the set) when the element was never added, i.e. it *should* say "false".
However, it will *never* say "false" for a member that is actually in the set.
Effectively, you can ask if it's **possible** that an element is in the set, and the answer could either be "no" or "maybe".

Why should you be okay with that?
For many applications, you shouldn't be.
Definitive answers are often required.
However, *sometimes* it's tolerable and in fact worth the trade-off.
For example, databases can use them to avoid unnecessary disk access if it can be sure the key is not in the database.
Hash sets or tree sets would be unacceptable in these situations if there are millions or perhaps billions of keys.
At the least, those deterministic sets must store the keys themselves which is expensive in regards to space.

Suppose you store 100,000,000 strings 16-characters long.
That is at *least* 1.5GB of storage.
A Bloom filter with 100,000,000 keys having a false positive rate of 1% only needs about 114MB.

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
