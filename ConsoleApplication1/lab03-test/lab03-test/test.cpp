#include "histogram.h"

#include <cassert>

void
test_positive() {
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

int
main() {
    test_positive();
}