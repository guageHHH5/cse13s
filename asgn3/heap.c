#include "heap.h"

#include "stats.h"

#include <stdbool.h>

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && (cmp(stats, A[right - 1], A[left - 1]) == 1)) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t minji = first;
    uint32_t great = max_child(stats, A, minji, last);

    while (minji <= last / 2 && !found) {
        if (cmp(stats, A[minji - 1], A[great - 1]) == -1) {
            swap(stats, &A[minji - 1], &A[great - 1]);
            minji = great;
            great = max_child(stats, A, minji, last);
        } else {
            found = true;
        }
    }
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t danheng = (last / 2); danheng > (first - 1); danheng--) {
        fix_heap(stats, A, danheng, last);
    }
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
}
