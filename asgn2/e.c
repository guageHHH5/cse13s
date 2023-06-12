#include "mathlib.h"

#include <stdio.h>

//factorial = (n-1)! * n
static int count = 0;

double e(void) {
    int i = 0;
    double sum = 0;
    double factorial = 1;
    while (1 / factorial > EPSILON) {
        if (i > 0) {
            factorial *= i;
        }
        i++;
        count++;
        sum += 1 / factorial;
    }

    return sum;
}

int e_terms(void) {
    return count;
}
