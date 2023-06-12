#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "Hahbsqin:p:r:"

void sortfunc(Stats *stats, uint32_t *A, uint32_t n, int alg) {
    if (alg == 0) {
        insertion_sort(stats, A, n);
        printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", n, stats->moves,
            stats->compares);
        return;
    }

    if (alg == 1) {
        heap_sort(stats, A, n);
        printf(
            "Heap Sort, %d elements, %lu moves, %lu compares\n", n, stats->moves, stats->compares);
        return;
    }

    if (alg == 2) {
        shell_sort(stats, A, n);
        printf(
            "Shell Sort, %d elements, %lu moves, %lu compares\n", n, stats->moves, stats->compares);
        return;
    }

    if (alg == 3) {
        quick_sort(stats, A, n);
        printf(
            "Quick Sort, %d elements, %lu moves, %lu compares\n", n, stats->moves, stats->compares);
        return;
    }

    if (alg == 4) {
        batcher_sort(stats, A, n);
        printf("Batcher Sort, %d elements, %lu moves, %lu compares\n", n, stats->moves,
            stats->compares);
        return;
    }
}

int main(int argc, char **argv) {
    int opt = 0;
    Set new_set = set_empty();
    int testi = 0;
    int tests = 2;
    int testh = 1;
    int testq = 3;
    int testb = 4;
    bool testH = false;
    bool test_modCheck = false;
    uint32_t seed = 13371453;
    uint32_t elements = 100;
    uint32_t size = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            new_set = set_universal();
            // new_set = set_insert(new_set, testi);
            // new_set = set_insert(new_set, testh);
            break;
        case 'i': new_set = set_insert(new_set, testi); break;
        case 'b': new_set = set_insert(new_set, testb); break;
        case 's': new_set = set_insert(new_set, tests); break;
        case 'h': new_set = set_insert(new_set, testh); break;
        case 'q': new_set = set_insert(new_set, testq); break;
        case 'r': seed = strtod(optarg, NULL); break;
        case 'p': elements = strtod(optarg, NULL); break;
        case 'n': size = strtod(optarg, NULL); break;
        default: testH = true;
        }
    }

    test_modCheck
        = (testi == false && testb == false && tests == false && testh == false && testq == false);
    (void) testH;
    (void) test_modCheck;
    if (new_set == set_empty()) {
        testi = testb = tests = testh = testq = false;
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./sorting [-Hahbsqi] [-n length] [-p elements] [-r seed]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("   -H              Display program help and usage.\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -h              Enable Heap Sort.\n");
        printf("   -b              Enable Batcher Sort.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -q              Enable Quick Sort.\n");
        printf("   -i              Enable Insertion Sort.\n");
        printf("   -n length       Specify number of array elements (default: 100).\n");
        printf("   -p elements     Specify number of elements to print (default: 100).\n");
        printf("   -r seed         Specify random seed (default: 13371453).\n");
    }

    (void) elements;

    uint32_t A[size];
    Stats new_stats = { 0, 0 };

    for (int alg = 0; alg < 5; alg++) {
        srandom(seed);
        uint32_t mask = 0x3FFFFFFF;
        for (uint32_t i = 0; i < size; i++) {
            A[i] = random() & mask;
        }
        if (set_member(new_set, alg)) {
            sortfunc(&new_stats, A, size, alg);
            for (uint32_t i = 0; i < elements; i++) {
                if (elements > size) {
                    elements = size;
                }
                printf("%13" PRIu32, A[i]);
                if (((i + 1) % 5 == 0 && i != 0) || i + 1 == elements) {
                    printf("\n");
                }
            }
            reset(&new_stats);
        }
    }
    return 0;
}
