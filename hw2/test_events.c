#include <criterion/criterion.h>
#include "events.h"

/*
 * Public sanity tests. These are a SUBSET of the tests used for grading -
 * passing all of these does not guarantee full marks, but failing them means
 * something is clearly wrong. Run with `make test`.
 *
 * Criterion provides its own main(), so there is none here.
 */

/* ---- Part 1 - Datetime codec ---- */

Test(dt_pack, basics) {
    /* All-zero fields (except a year of 0) pack to 0. */
    cr_assert_eq(dt_pack(0, 0, 0, 0, 0, 0), 0);
    /* second occupies the low 6 bits. */
    cr_assert_eq(dt_pack(0, 0, 0, 0, 0, 5), 5);
    /* minute occupies bits 6..11, so minute 1 is 1 << 6 == 64. */
    cr_assert_eq(dt_pack(0, 0, 0, 0, 1, 0), 64);
}

Test(dt_pack, ordering) {
    /* A larger packed value must mean a later datetime, across every field. */
    uint64_t a = dt_pack(2024, 1, 1, 0, 0, 0);
    uint64_t b = dt_pack(2026, 7, 15, 9, 30, 0);
    uint64_t c = dt_pack(2026, 7, 15, 9, 30, 1);
    cr_assert(a < b, "earlier year is smaller");
    cr_assert(b < c, "one second later is larger");
}

Test(dt_unpack, roundtrip) {
    int y, mo, d, h, mi, s;
    dt_unpack(dt_pack(2026, 7, 15, 9, 30, 45), &y, &mo, &d, &h, &mi, &s);
    cr_assert_eq(y, 2026);
    cr_assert_eq(mo, 7);
    cr_assert_eq(d, 15);
    cr_assert_eq(h, 9);
    cr_assert_eq(mi, 30);
    cr_assert_eq(s, 45);
}

Test(dt_valid, basics) {
    cr_assert_eq(dt_valid(2026, 7, 15, 9, 30, 0), 1);
    cr_assert_eq(dt_valid(2026, 13, 1, 0, 0, 0), 0);   /* month out of range */
    cr_assert_eq(dt_valid(2026, 7, 15, 24, 0, 0), 0);  /* hour out of range */
}

/* ---- Part 2 - Array-based max-heap ---- */

Test(heap_peek, returns_max) {
    uint64_t *h = heap_create(8);
    cr_assert_not_null(h);
    int size = 0;
    heap_push(h, &size, 8, 30);
    heap_push(h, &size, 8, 10);
    heap_push(h, &size, 8, 50);
    heap_push(h, &size, 8, 20);
    cr_assert_eq(heap_peek(h), 50, "largest value sits at the root");
    cr_assert_eq(size, 4);
    heap_free(h);
}

Test(heap_pop, returns_descending) {
    uint64_t vals[] = {30, 10, 50, 20, 40};
    uint64_t *h = heap_create(5);
    cr_assert_not_null(h);
    int size = 0;
    for (int i = 0; i < 5; i++) {
        heap_push(h, &size, 5, vals[i]);
    }
    cr_assert_eq(heap_pop(h, &size), 50);
    cr_assert_eq(heap_pop(h, &size), 40);
    cr_assert_eq(heap_pop(h, &size), 30);
    cr_assert_eq(heap_pop(h, &size), 20);
    cr_assert_eq(heap_pop(h, &size), 10);
    cr_assert_eq(size, 0);
    heap_free(h);
}

/* ---- Part 3 - Heapsort ---- */

Test(heapsort, basic) {
    uint64_t a[] = {30, 10, 50, 20, 40};
    heapsort(a, 5);
    uint64_t want[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        cr_assert_eq(a[i], want[i], "index %d", i);
    }
}

Test(heapsort, datetimes_chronological) {
    uint64_t a[] = {
        dt_pack(2026, 7, 15, 9, 30, 0),
        dt_pack(2024, 1, 1, 0, 0, 0),
        dt_pack(2026, 7, 15, 9, 29, 59),
    };
    heapsort(a, 3);
    cr_assert(a[0] < a[1], "first is earliest");
    cr_assert(a[1] < a[2], "sorted ascending == chronological");
    cr_assert_eq(a[0], dt_pack(2024, 1, 1, 0, 0, 0));
}
