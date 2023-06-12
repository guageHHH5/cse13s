#include "bmp.h"
#include "io.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

int main(int argc, char **argv) {
    int opt = 0;
    bool testi = false;
    bool testo = false;
    bool testh = false;

    char *in = NULL;
    char *out = NULL;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            in = optarg;
            testi = true;
            break;
        case 'o':
            out = optarg;
            testo = true;
            break;
        case 'h': testh = true; break;
        }
    }
    if (testh) {
        printf("Usage: colorb -i infile -o outfile\n");
        printf("       colorb -h\n");
        return 0;
    }
    if (testi == false) {
        printf("ERROR: must provide input file with -i option\n");
        printf("Usage: colorb -i infile -o outfile\n");
        printf("       colorb -h\n");
        return 0;
    }
    if (testo == false) {
        printf("ERROR: must provide input file with -o option\n");
        printf("Usage: colorb -i infile -o outfile\n");
        printf("       colorb -h\n");
        return 0;
    }

    Buffer *rbuf = read_open(in);
    if (rbuf == NULL) {
        printf("ERROR: cannot read file %s\n", in);
        printf("Usage: colorb -i infile -o outfile\n");
        printf("       colorb -h\n");
        return 0;
    }
    Buffer *wbuf = write_open(out);

    BMP *rbmp = bmp_create(rbuf);
    bmp_reduce_palette(rbmp);
    bmp_write(rbmp, wbuf);

    read_close(&rbuf);
    write_close(&wbuf);
    bmp_free(&rbmp);
    return 0;
}
