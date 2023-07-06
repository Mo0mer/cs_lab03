#include "histogram.h"
#include "pr_hist.h"

#include <cassert>

void test_find_min_max() {
    double min = 0;
    double max = 0;

    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);

    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);

    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);

    find_minmax({ 7, 7, 7 }, min, max);
    assert(min == 7);
    assert(max == 7);

}

void test_make_histogram() {

    vector<size_t> result = { 2, 2 };
    assert(make_hist({ 1, 2, 3, 4 }, 2, 4, 1, 4) == result);
    result.assign({ 3, 3, 4 });
    assert(make_hist({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, 3, 10, 1, 10) == result);

}

void test_find_max_count() {
    assert(find_max_count({ 1, 1, 1, 2, 2, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5 }) == 5);
    assert(find_max_count({}) == 0);
}

int
main() {
    test_find_min_max();
    test_make_histogram();
    test_find_max_count();
}