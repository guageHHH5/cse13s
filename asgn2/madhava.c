#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_madhava(void) {
    double k = 1, i = 1, old_val, new_val = 1;
    count = 1;
    do {
        old_val = new_val;
        k += 2;
        i = i * (-3);
        new_val = new_val + (1 / (k * i));
        count++;
    } while (absolute(new_val - old_val) > EPSILON);
    return sqrt_newton(12) * new_val;
}

int pi_madhava_terms(void) {
    return count;
}
