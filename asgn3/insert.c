#include "insert.h"

#include "stats.h"

// start at index 0
void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t i = 1; i < length; i++) {
        uint32_t j = i;
        uint32_t temp = move(stats, arr[i]);
        while (j > 0 && (cmp(stats, temp, arr[j - 1]) == -1)) {
            arr[j] = move(stats, arr[j - 1]);
            j -= 1;
        }
        arr[j] = move(stats, temp);
    }
}
