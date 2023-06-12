#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvwnsh"

int main(int argc, char **argv) {
    int opt = 0;
    double pi = M_PI;
    double e_func = M_E;
    double diff = 0.0;
    bool teste = false;
    bool testb = false;
    bool testm = false;
    bool testr = false;
    bool testv = false;
    bool testw = false;
    bool testn = false;
    bool tests = false;
    bool testh = false;
    bool test_modCheck = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': teste = testb = testm = testr = testv = testw = testn = true; break;
        case 'e': teste = true; break;
        case 'r': testr = true; break;
        case 'b': testb = true; break;
        case 'm': testm = true; break;
        case 'v': testv = true; break;
        case 'w': testw = true; break;
        case 'n': testn = true; break;
        case 's': tests = true; break;
        case 'h': testh = true; break;
        default: testh = true;
        }
    }

    test_modCheck = (teste == false && testr == false && testb == false && testm == false
                     && testv == false && testw == false && testn == false);
    if (testh || test_modCheck) {
        teste = testb = testm = testr = testv = testw = testn = false;
        printf("SYNOPSIS\n");
        printf("   A test harness for small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test -[aebmrvwnsh]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e tests.\n");
        printf("  -b   Runs BBP tests.\n");
        printf("  -m   Runs Madhava tests.\n");
        printf("  -r   Runs Euler tests.\n");
        printf("  -v   Runs Viete tests.\n");
        printf("  -w   Runs Wallis tests.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
    }
    if (teste) {
        double my_e = e();
        diff = e_func - my_e;
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", my_e, e_func, diff);
        if (tests) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (testb) {
        double bbp = pi_bbp();
        diff = absolute(bbp - pi);
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", bbp, pi, diff);
        if (tests) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (testm) {
        double madhava = pi_madhava();
        diff = pi - madhava;
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", madhava, pi, diff);
        if (tests) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (testr) {
        double euler = pi_euler();
        diff = absolute(euler - pi);
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", euler, pi, diff);
        if (tests) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (testv) {
        double viete = pi_viete();
        diff = absolute(viete - pi);
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", viete, pi, diff);
        if (tests) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (testw) {
        double wallis = pi_wallis();
        diff = absolute(wallis - pi);
        printf("pi_wallis() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", wallis, pi, diff);
        if (tests) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
    }
    if (testn) {
        for (double x = 0.0; x < 9.9; x = x + 0.1) {
            double s_n = sqrt_newton(x);
            double s = sqrt(x);
            diff = s - s_n;
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", x,
                s_n, x, s, diff);
            if (tests) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    return 0;
}
