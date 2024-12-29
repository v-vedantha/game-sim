#include "TestUtils.h"
#include <stdlib.h>

// Not sure what the import for std::abs is
#include <iostream>

bool isNear(double expected, double actual) {
    return std::abs(expected - actual) < 0.1;
}
