#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h>

/*
 * events.h - Event Log Sorter (CMSC 14300, HW2)
 *
 * You will build three things and then use them together to sort a log of
 * timestamped events into chronological order:
 *
 *   Part 1 - a datetime "codec" that packs a calendar timestamp into a single
 *            64-bit integer using bit operations,
 *   Part 2 - an array-based binary MAX-heap (a priority queue) held in memory
 *            you allocate on the heap yourself, and
 *   Part 3 - heapsort, built on top of that heap.
 *
 * You may NOT use qsort (from <stdlib.h>) anywhere - the point is to build the
 * sorting yourself.
 */

/* ===========================================================================
 * Part 1 - Datetime codec (bit manipulation)
 *
 * A datetime is packed into the low 40 bits of a uint64_t. The fields are laid
 * out from most-significant to least-significant so that a LARGER packed value
 * is always a LATER datetime. That single property is what makes Parts 2 and 3
 * easy: comparing two timestamps is just comparing two uint64_t values.
 *
 *   bits 39..26 (14 bits) : year    (0 .. 16383)
 *   bits 25..22 ( 4 bits) : month   (1 .. 12)
 *   bits 21..17 ( 5 bits) : day     (1 .. 31)
 *   bits 16..12 ( 5 bits) : hour    (0 .. 23)
 *   bits 11..6  ( 6 bits) : minute  (0 .. 59)
 *   bits  5..0  ( 6 bits) : second  (0 .. 59)
 *
 * The top 24 bits are always 0.
 * ========================================================================= */

/*
 * Pack the six fields into a single 64-bit timestamp using shifts and bitwise
 * OR, following the layout above. You may assume every field is in range.
 */
uint64_t dt_pack(int year, int month, int day, int hour, int minute, int second);

/*
 * Reverse of dt_pack: recover each field from a packed timestamp using shifts
 * and masks, writing each value through its out-pointer. None of the pointers
 * are NULL.
 */
void dt_unpack(uint64_t t, int *year, int *month, int *day,
               int *hour, int *minute, int *second);

/*
 * Return 1 if the six fields form a valid datetime (each within the range
 * shown in the layout above), else 0.
 */
int dt_valid(int year, int month, int day, int hour, int minute, int second);

/* ===========================================================================
 * Part 2 - Array-based max-heap / priority queue
 *
 * The heap is just a plain array of uint64_t timestamps, stored on the heap
 * (the malloc/free region), plus a separate `size` you keep track of. There is
 * no struct: you pass the array, its current size, and its capacity explicitly,
 * exactly as you passed arrays and their length in Lecture 4.
 *
 * It is a MAX-heap: the largest value (the latest datetime) is always at the
 * root, index 0. For a node at index i:
 *     parent(i) = (i - 1) / 2
 *     left(i)   = 2*i + 1
 *     right(i)  = 2*i + 2
 * ========================================================================= */

/*
 * Allocate a heap that can hold up to `capacity` timestamps and return a
 * pointer to it (the caller owns it and must later call heap_free). Return NULL
 * if capacity is not positive or if allocation fails. The heap starts empty, so
 * the caller also keeps a size that starts at 0.
 */
uint64_t *heap_create(int capacity);

/* Free a heap returned by heap_create. Passing NULL is allowed and does nothing. */
void heap_free(uint64_t *heap);

/*
 * Insert `value` into the heap and restore the max-heap order (sift up). `size`
 * points at the heap's current element count and is increased by one on a
 * successful insert. If the heap is already full (*size == capacity), leave the
 * heap and *size unchanged.
 */
void heap_push(uint64_t *heap, int *size, int capacity, uint64_t value);

/*
 * Remove and return the maximum element (the root). `size` points at the
 * current element count and is decreased by one. The remaining elements are
 * restored to max-heap order (sift down). You may assume *size > 0.
 */
uint64_t heap_pop(uint64_t *heap, int *size);

/*
 * Return the maximum element (the root) without removing it. You may assume the
 * heap is non-empty.
 */
uint64_t heap_peek(uint64_t *heap);

/* ===========================================================================
 * Part 3 - Heapsort
 * ========================================================================= */

/*
 * Sort arr[0..n-1] in ascending order, in place, using max-heap logic: turn the
 * array into a max-heap, then repeatedly move the root to the end. Because a
 * larger packed value is a later datetime, ascending order is chronological
 * order.
 */
void heapsort(uint64_t *arr, int n);

/* ===========================================================================
 * STRETCH (ungradedan auto-growing heap
 *
 * Like heap_push, but instead of ignoring a value when the heap is full, grow
 * the backing array (double its capacity) with realloc. Because realloc may
 * move the block, this returns the heap's (possibly new) base pointer and
 * updates *capacity. On a successful call *size increases by one. If a needed
 * reallocation fails, return NULL and leave *size and the old heap unchanged.
 *
 * If you do not attempt the stretch, leave the provided stub in events.c as-is;
 * the extra-credit test will simply score 0.
 * ========================================================================= */
uint64_t *heap_push_grow(uint64_t *heap, int *size, int *capacity, uint64_t value);

#endif /* EVENTS_H */
