#include "stack.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Running one item stack test\n");
    // Create a stack that can only hold one item
    Stack *s = stack_create(1);
    // Add 10 to the stack
    assert(stack_push(s, 10));
    // make srue that the top of the stack is 10 when we peek!
    uint32_t x = 0;
    assert(stack_peek(s, &x));
    assert(x == 10);
    // make sure the stack is full!
    assert(stack_full(s));
    x = 2;
    // Make sure we can remove the item from the stack
    stack_pop(s, &x);
    assert(x == 10);
    assert(stack_empty(s));

    // Free up so valgrind passes
    stack_free(&s);
    printf("One item stack tests complete. Be sure to rerun with valgrind!\n");

    return 0;
}
