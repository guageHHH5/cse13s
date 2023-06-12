#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "dhi:o:"
static bool direct = false;
static bool help = false;

static uint32_t vertices;
static bool first = true; // check for first path in DFS procedure

void DFS(Graph *g, uint32_t v, Path *current, Path *shortest, char *cities[]) {
    graph_visit_vertex(g, v); // visit vertex

    // if current path ever exceeds shortest stop computing it
    if (path_distance(current) >= path_distance(shortest) && path_distance(shortest) != 0) {
        return;
    }

    if ((path_vertices(current) == graph_vertices(g) - 1)
        && graph_get_weight(g, v, START_VERTEX) != 0) {
        path_add(current, START_VERTEX, g);
        if (path_distance(current) < path_distance(shortest) || first) {
            path_copy(shortest, current);
            first = false;
        }
        path_remove(current, g);
    }

    for (uint32_t i = 0; i < graph_vertices(g); i += 1) {
        if (graph_get_weight(g, v, i) != 0 && !graph_visited(g, i)) {
            graph_visit_vertex(g, i);
            path_add(current, i, g);

            DFS(g, i, current, shortest, cities);
            graph_unvisit_vertex(g, i);
            path_remove(current, g);
        }
    }
}

int main(int argc, char **argv) {
    FILE *in = stdin;
    FILE *out = stdout;
    int opt = 0;
    opterr = 0; // disable getopt default invalid msg
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case '?': {
            char c = optopt;
            fprintf(stderr, "tsp:  unknown or poorly formatted option -%c\n", c);
            return 0;
            break;
        }
        case 'h': help = true; break;

        case 'd': direct = true; break;
        case 'i': {
            in = fopen(optarg, "r");
            if (in == NULL) {
                fprintf(stderr, "tsp:  error reading input file %s\n", optarg);
                return 0;
            }
            break;
        }

        case 'o': out = fopen(optarg, "w"); break;
        default: break;
        }
    }

    if (help) {
        printf("Usage: tsp [options]\n");
        printf("\n");
        printf("-i infile    Specify the input file path containing the cities and edges\n"
               "             of a graph. If not specified, the default input should be\n"
               "             set as stdin.\n");
        printf("\n");
        printf("-o outfile   Specify the output file path to print to. If not specified,\n");
        printf("             the default output should be set as stdout.");
        printf("\n");
        printf("-d           Specifies the graph to be directed.\n");
        printf("-h           Prints out a help message describing the purpose of the\n");
        printf("             graph and the command-line options it accepts, exiting the\n");
        printf("             program afterwards.\n");
        return 0;
    }

    // standard character buffer
    char buffer[1024];

    fscanf(in, "%" SCNu32 "\n", &vertices); // read first line

    // create graph
    Graph *g = graph_create(vertices, direct);

    // allocate mem for string array
    char **citynames = (char **) calloc(vertices, sizeof(char *));

    // add names to array
    for (uint32_t i = 0; i < vertices; i += 1) {
        fgets(buffer, 1024, in);
        buffer[strlen(buffer) - 1] = '\0';
        graph_add_vertex(g, buffer, i); // add name to graph name array
        citynames[i] = strdup(buffer);
    }

    static uint32_t points;
    fscanf(in, "%" SCNu32 "\n", &points); // read # of graph points

    uint32_t a, b, c;

    // read all start, end, weight graph pairs and insert into graph
    for (uint32_t i = 0; i < points; i += 1) {
        fscanf(in, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &a, &b, &c);
        graph_add_edge(g, a, b, c);
    }

    fclose(in);

    Path *current = path_create(vertices);
    Path *shorter = path_create(vertices);

    DFS(g, START_VERTEX, current, shorter, citynames); // dfs procedure

    // no path was found returning to START_VERTEX
    if (path_distance(shorter) == 0) {
        fprintf(out, "No path found! Alissa is lost!\n");
        for (uint32_t i = 0; i < vertices; i += 1) {
            free(citynames[i]);
        }
        free(citynames);
        graph_free(&g);
        path_free(&current);
        path_free(&shorter);
        return 0;
    }
    // otherwise shortest hamiltonian path was found and print
    path_print(shorter, out, g);

    fclose(out); // close outfile

    for (uint32_t i = 0; i < vertices; i += 1) {
        free(citynames[i]);
    }
    free(citynames);

    graph_free(&g);
    path_free(&current);
    path_free(&shorter);
    return 0;
}
