#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_bbp(void) {
    double i = 1.0, k = 0.0, sum = 0.0;
    while (((1 / i)
               * ((4 / ((8 * k) + 1)) - (2 / ((8 * k) + 4)) - (1 / ((8 * k) + 5))
                   - (1 / ((8 * k) + 6))))
           > EPSILON) {
        sum += ((1 / i)
                * ((4 / ((8 * k) + 1)) - (2 / ((8 * k) + 4)) - (1 / ((8 * k) + 5))
                    - (1 / ((8 * k) + 6))));
        count++;
        k++;
        i *= 16;
    }
    return sum;
}

int pi_bbp_terms(void) {
    return count;
}
