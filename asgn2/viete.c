#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_viete(void) {
    double numerator = sqrt_newton(2), product = 1;
    while (numerator < (2 - EPSILON)) {
        product *= (numerator / 2);
        numerator = sqrt_newton(2 + numerator);
        count++;
    }
    return (2 / product);
}

int pi_viete_factors(void) {
    return count;
}
