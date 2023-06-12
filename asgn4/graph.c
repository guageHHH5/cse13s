#include "graph.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for (uint32_t i = 0; i < vertices; i++) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }

    return g;
}

void graph_free(Graph **gp) {
    if (gp != NULL && *gp != NULL) {
        if ((*gp)->visited) {
            free((*gp)->visited);
            (*gp)->visited = NULL;
        }
        if ((*gp)->names) {
            for (uint32_t i = 0; i < (*gp)->vertices; i++) {
                free((*gp)->names[i]);
            }
            free((*gp)->names);
            (*gp)->names = NULL;
        }
        if ((*gp)->weights) {
            for (uint32_t i = 0; i < (*gp)->vertices; i++) {
                free((*gp)->weights[i]);
            }
            free((*gp)->weights);
            (*gp)->weights = NULL;
        }
        free(*gp);
    }
    if (gp != NULL) {
        *gp = NULL;
    }
    return;
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (start < g->vertices && start >= 0 && end < g->vertices && end >= 0) {
        g->weights[start][end] = weight;
        if (!g->directed) {
            g->weights[end][start] = weight;
        }
    }
    return;
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    if (start < g->vertices && start >= 0 && end < g->vertices && end >= 0
        && g->weights[start][end] > 0) {
        return g->weights[start][end];
    }
    return 0;
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    if (v < g->vertices && v >= 0) {
        g->visited[v] = true;
    }
    return;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (v < g->vertices && v >= 0) {
        g->visited[v] = false;
    }
    return;
}

bool graph_visited(const Graph *g, uint32_t v) {
    if (g->visited[v] == true) {
        return true;
    }
    return false;
}

char **graph_get_names(const Graph *g) {
    return g->names;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v]) {
        free(g->names[v]);
    }
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

void graph_print(const Graph *g) {
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            printf("%2" PRIu32 " ", g->weights[i][j]);
            if (j == g->vertices - 1) {
                printf("\n");
            }
        }
    }
    return;
}
