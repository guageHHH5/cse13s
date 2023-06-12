#include "path.h"

#include "graph.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t edge;

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(capacity);
    p->total_weight = 0;
    return p;
}

void path_free(Path **pp) {
    if (*pp && (*pp)->vertices) {
        stack_free(&((*pp)->vertices));
        if ((*pp)->vertices) {
            free((*pp)->vertices);
            (*pp)->vertices = NULL;
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
    return;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_full(p->vertices)) {
        return;
    } else {
        if (stack_empty(p->vertices)) {
            edge = graph_get_weight(g, 0, val);
        } else {
            uint32_t coord_start;
            stack_peek(p->vertices, &coord_start);
            edge = graph_get_weight(g, coord_start, val);
        }
        stack_push(p->vertices, val);
        p->total_weight += edge;
        return;
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    if (stack_empty(p->vertices)) {
        return 0;
    } else {
        uint32_t peek_v;
        uint32_t pop_v;
        stack_pop(p->vertices, &pop_v);
        if (path_vertices(p) == 0) {
            edge = graph_get_weight(g, 0, pop_v);
        } else {
            stack_peek(p->vertices, &peek_v);
            edge = graph_get_weight(g, peek_v, pop_v);
        }
        p->total_weight -= edge;
        return 1;
    }
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
    return;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    fprintf(f, "Alissa starts at:\n");
    fprintf(f, "%s\n", graph_get_vertex_name(g, 0));
    stack_print(p->vertices, f, graph_get_names(g));
    fprintf(f, "Total Distance: %" PRIu32 "\n", p->total_weight);
    return;
}
