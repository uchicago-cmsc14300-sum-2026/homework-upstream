#include <stdlib.h>
#include "events.h"

/*
 * events.c - IMPLEMENT THE FUNCTIONS BELOW.
 *
 * Rules:
 *   - Do NOT use qsort. Build the heap and the sort yourself.
 *   - Compile cleanly with: -Wall -Wextra -Werror -std=c17
 *   - Every malloc/realloc you make must have a matching free (heap_free frees
 *     what heap_create allocated). Run valgrind to check for leaks.
 *
 * You may add your own small static helper functions in this file (for example
 * a swap, a sift-up, and a sift-down). The (void) lines below just silence
 * "unused parameter" warnings in the stubs; delete them as you implement.
 */

/* ---- Part 1 - Datetime codec ---- */

uint64_t dt_pack(int year, int month, int day, int hour, int minute, int second) {
    /* TODO: pack the six fields into one uint64_t using shifts and | . 
       Replace the code below with your implementation. */
    (void) year; (void) month; (void) day;
    (void) hour; (void) minute; (void) second;
    return 0;
}

void dt_unpack(uint64_t t, int *year, int *month, int *day,
               int *hour, int *minute, int *second) {
    /* TODO: recover each field with shifts and masks, writing through the
     * out-pointers. Replace the code below with your implementation.*/
    (void) t;
    (void) year; (void) month; (void) day;
    (void) hour; (void) minute; (void) second;
}

int dt_valid(int year, int month, int day, int hour, int minute, int second) {
    /* TODO: return 1 if every field is in range, else 0. 
     * Replace the code below with your implementation. */
    (void) year; (void) month; (void) day;
    (void) hour; (void) minute; (void) second;
    return 0;
}

/* ---- Part 2 - Array-based max-heap ---- */

uint64_t *heap_create(int capacity) {
    /* TODO: malloc room for `capacity` timestamps; return NULL on bad capacity
     * or allocation failure. Replace the code below with your implementation.*/
    (void) capacity;
    return NULL;
}

void heap_free(uint64_t *heap) {
    /* TODO: free the heap (free(NULL) is fine). 
     * Replace the code below with your implementation. */
    (void) heap;
}

void heap_push(uint64_t *heap, int *size, int capacity, uint64_t value) {
    /* TODO: if there is room, place value at the end and sift it up, then
     * increase *size. If full, do nothing. Replace the code below with your 
     * implementation.*/
    (void) heap; (void) size; (void) capacity; (void) value;
}

uint64_t heap_pop(uint64_t *heap, int *size) {
    /* TODO: save the root, move the last element to the root, shrink *size,
     * sift down, and return the saved root. Assume *size > 0. 
     * Replace the code below with your implementation.*/
    (void) heap; (void) size;
    return 0;
}

uint64_t heap_peek(uint64_t *heap) {
    /* TODO: return the root without removing it. 
     * Replace the code below with your implementation. */
    (void) heap;
    return 0;
}

/* ---- Part 3 - Heapsort ---- */

void heapsort(uint64_t *arr, int n) {
    /* TODO: build a max-heap in place, then repeatedly swap the root to the end
     * and sift down over the shrinking heap. 
     * Replace the code below with your implementation. */
    (void) arr; (void) n;
}

/* ---- STRETCH (ungraded) - auto-growing heap ----
 * If you do not attempt the stretch, leave this stub as-is; the extra-credit
 * test will simply score 0. */

uint64_t *heap_push_grow(uint64_t *heap, int *size, int *capacity, uint64_t value) {
    /* TODO (optional): if full, double the capacity with realloc; then insert
     * and sift up. Return the (possibly moved) base pointer, or NULL if a
     * needed realloc fails. */
    (void) heap; (void) size; (void) capacity; (void) value;
    return NULL;
}
