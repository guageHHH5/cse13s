#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, double weight) {
    Node *n = malloc(sizeof(Node));
    n->symbol = symbol;
    n->weight = weight;
    n->left = NULL; //new
    n->right = NULL; //new
    return n;
}
void node_free(Node **node) {
    free(*node);
    *node = NULL;
    return;
}
void node_print_tree(Node *tree, char ch, int indentation) {
    if (tree == NULL) {
        return;
    }
    node_print_tree(tree->right, '/', indentation + 3);
    printf("%*cweight = %.0f", indentation + 1, ch, tree->weight);

    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }

    printf("\n");
    node_print_tree(tree->left, '\\', indentation + 3);
}
