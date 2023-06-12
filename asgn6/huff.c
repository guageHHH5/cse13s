#include "bitwriter.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    uint64_t filesize = 0;
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0.0;
    }
    // might be bad
    uint8_t x;
    while (read_uint8(inbuf, &x)) {
        ++histogram[x];
        ++filesize;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    return filesize;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *q = pq_create();
    // might be bad

    for (int i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            Node *n = node_create(i, histogram[i]);
            enqueue(q, n);
            ++(*num_leaves);
        }
    }
    Node *left;
    Node *right;
    while (!pq_is_empty(q) && !pq_size_is_1(q)) {
        dequeue(q, &left);
        dequeue(q, &right);
        Node *minji = node_create('$', left->weight + right->weight);
        minji->left = left;
        minji->right = right;

        enqueue(q, minji);
        // node_free(left);
        // node_free(right);
    }
    Node *copium;
    dequeue(q, &copium);
    pq_free(&q);
    return copium;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL || node->right != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
    return;
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left != NULL || node->right != NULL) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
    return;
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    huff_write_tree(outbuf, code_tree);
    uint8_t b;
    while (read_uint8(inbuf, &b)) {
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (uint8_t i = 0; i <= code_length - 1; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
    return;
}

void free_all_nodes(Node **node) {
    if (*node) {
        free_all_nodes(&(*node)->left);
        free_all_nodes(&(*node)->right);
        // if leaf, then free
        if (!((*node)->left) && !((*node)->right)) {
            node_free(node);
        }
    }

    return;
}

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
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile");
        printf("       huff -h\n");
        return 0;
    }
    if (testi == false) {
        printf("ERROR: must provide input file with -i option\n");
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile");
        printf("       huff -h\n");
        return 0;
    }
    if (testo == false) {
        printf("ERROR: must provide input file with -o option\n");
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile");
        printf("       huff -h\n");
        return 0;
    }

    Buffer *rbuf = read_open(in);
    if (rbuf == NULL) {
        printf("ERROR: cannot read file %s\n", in);
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile");
        printf("       huff -h\n");
        return 0;
    }
    double histogram[256];
    uint64_t filesize = fill_histogram(rbuf, histogram);

    uint16_t num_leaves = 0;
    Node *node = create_tree(histogram, &num_leaves);

    //maybe
    Code code_table[256];
    fill_code_table(code_table, node, 0, 0);

    read_close(&rbuf);

    rbuf = read_open(in);
    BitWriter *wbuf = bit_write_open(out);
    huff_compress_file(wbuf, rbuf, (uint32_t) filesize, num_leaves, node, code_table);
    read_close(&rbuf);
    bit_write_close(&wbuf);
    free_all_nodes(&node);
}
