#include <stdio.h>
#include "tap.h"
#include "bloom.h"

int main() {
    plan(18);
    BloomFilter *bf = bloom_filter_new(100, 0.1);

    cmp_ok(bloom_filter_false_positive_prob(bf), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "food"), "==", 0);
    bloom_filter_add(bf, "food");
    bloom_filter_add(bf, "bar");
    cmp_ok(bloom_filter_might_contain(bf, "food"), "==", 1);
    cmp_ok(bloom_filter_might_contain(bf, "sushi"), "==", 0);

    float fp_prob = bloom_filter_false_positive_prob(bf);
    ok(0.000001934854 < fp_prob && fp_prob < 0.000001934855);

    bool missing_no_items = 1;
    for (int i = 0; i < 98; i++) {
        char key[3];
        sprintf(key, "%d", i);
        bloom_filter_add(bf, key);
        missing_no_items *= bloom_filter_might_contain(bf, key);
    }
    cmp_ok(missing_no_items, "==", 1);

    fp_prob = bloom_filter_false_positive_prob(bf);
    ok(0.101055592298 < fp_prob && fp_prob < 0.101055592299);

    cmp_ok(bloom_filter_might_contain(bf, "100"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "101"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "102"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "103"), "==", 1);
    cmp_ok(bloom_filter_might_contain(bf, "104"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "105"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "106"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "107"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "108"), "==", 0);
    cmp_ok(bloom_filter_might_contain(bf, "109"), "==", 1);
    cmp_ok(bloom_filter_might_contain(bf, "110"), "==", 0);

    bloom_filter_free(bf);
    done_testing();
    return 0;
}