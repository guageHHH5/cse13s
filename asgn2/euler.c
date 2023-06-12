#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double pi_euler(void) {
    double k = 1.0;
    double sum = 0;
    while ((1 / (k * k)) > EPSILON) {
        sum += 1 / (k * k);
        k++;
        count++;
    }
    return sqrt_newton(6 * sum);
}

int pi_euler_terms(void) {
    return count;
}
