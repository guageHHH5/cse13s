#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_wallis(void) {
    double product = 1, k = 1;
    while (absolute(1.0 - ((4.0 * k * k) / ((4.0 * k * k) - 1))) > EPSILON) {
        product *= ((4.0 * k * k) / ((4.0 * k * k) - 1));
        count++;
        k++;
    }
    return 2 * product;
}

int pi_wallis_factors(void) {
    return count;
}
