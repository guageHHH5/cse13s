#include "pq.h"

#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }

    // pq->list = calloc(1, sizeof(ListElement));
    // if(pq->list == NULL){
    //     free(pq);
    //     pq = NULL;
    //     return NULL;
    // }

    return pq;
}

// what happens when not empty?
//call dequeue until empty
void pq_free(PriorityQueue **q) {
    // free((*q)->list);
    // (*q)->list = NULL;
    free(*q);
    *q = NULL;
}

// ?
bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    }
    if (q->list->next == NULL) {
        return true;
    }
    return false;
}

bool pq_less_than(Node *n1, Node *n2) {
    if (n1->weight < n2->weight) {
        return true;
    }
    if (n1->weight > n2->weight) {
        return false;
    }
    return n1->symbol < n2->symbol;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *e = malloc(sizeof(ListElement));
    if (e == NULL) {
        return;
    }
    e->tree = tree;
    e->next = NULL; // new
    if (q->list == NULL) {
        q->list = e;
    } else if (pq_less_than(e->tree, q->list->tree)) {
        e->next = q->list;
        q->list = e;
    } else {
        for (ListElement *iter = q->list; iter != NULL; iter = iter->next) {
            if (iter->next == NULL) {
                iter->next = e;
                break;
            } else if (pq_less_than(e->tree, iter->next->tree)) {
                e->next = iter->next;
                iter->next = e;
                break;
            }
        }
    }
}
bool dequeue(PriorityQueue *q, Node **tree) {
    if (pq_is_empty(q)) {
        return false;
    }
    //maybe
    ListElement *temp = q->list;
    // *tree = temp->tree;
    q->list = temp->next;
    *tree = temp->tree;
    // node_free(&temp->tree);
    free(temp);
    temp = NULL;
    return true;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("========================================\n");
        } else {
            printf("----------------------------------------\n");
        }
        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }
    printf("========================================\n");
}
