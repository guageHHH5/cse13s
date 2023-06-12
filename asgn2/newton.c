#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double sqrt_newton(double x) {
    double next_y = 1.0;
    double y = 0.0;
    count = 0;
    while (absolute(next_y - y) > EPSILON) {
        y = next_y;
        next_y = 0.5 * (y + x / y);
        count++;
    }
    return next_y;
}

int sqrt_newton_iters(void) {
    return count;
}
