#include "set.h"

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t Set;
uint32_t mask = 0x00000007;

/*
* This function returns an empty set.  You can assign its return value
* to a variable of type Set.
*/
Set set_empty(void) {
    return 0;
}

/*
* This function returns a set containing every possible element (all
* bits are set to 1).
*/
Set set_universal(void) {
    return set_complement(set_empty());
}

/*
* Determine whether the Set s has member x.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 31.
*
* Return value:  true (== 1) if x is in s
*                false (== 0) otherwise
*/
bool set_member(Set s, int x) {
    return (s & (0x1 << (x & mask)));
}

/*
* Add the member x to the Set s.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 31.
*
* Return value:  the new Set, which will contain member x.
*/
Set set_insert(Set s, int x) {
    return (s | (0x1 << (x & mask)));
}

/*
* Remove the member x from the Set s.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 31.
*
* Return value:  the new Set, which will not contain member x.
*/
Set set_remove(Set s, int x) {
    return (s & ~(0x1 << (x & mask)));
}

/*
* Compute the union of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain members that are in
*                either s or t.
*/
Set set_union(Set s, Set t) {
    return (s | t);
}

/*
* Compute the intersection of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that are in
*                both s and t.
*/
Set set_intersect(Set s, Set t) {
    return (s & t);
}

/*
* Compute the difference of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that are in
*                s but NOT in t.
*/
Set set_difference(Set s, Set t) {
    return (s & ~t);
}

/*
* Compute the complement of a set.
*
*   s:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that
*                are NOT in s.
*/
Set set_complement(Set s) {
    return ~s;
}
