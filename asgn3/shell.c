#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <string.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (int gap = 0; gap < GAPS; gap++) {
        for (uint32_t i = gaps[gap]; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= gaps[gap] && (cmp(stats, temp, A[j - gaps[gap]]) == -1)) {
                A[j] = move(stats, A[j - gaps[gap]]);
                j -= gaps[gap];
            }
            A[j] = move(stats, temp);
        }
    }
}
