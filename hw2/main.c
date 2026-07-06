#include <stdio.h>
#include <stdlib.h>
#include "events.h"

/*
 * main.c - the Event Log Sorter app (Part 3).
 *
 * Reads a count N, then N event timestamps (one per line, as six integers
 * YYYY MM DD HH MM SS), packs each into a 64-bit value with dt_pack, sorts them
 * with your heapsort, and prints them back in chronological order.
 *
 * You should not need to change this file - it just uses the functions you
 * write in events.c. Build and run with `make` then `./app`.
 */

int main(void) {
    int n;
    printf("How many events? ");
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    /* One malloc for n timestamps; freed once at the end. */
    uint64_t *events = malloc((size_t) n * sizeof(uint64_t));
    if (events == NULL && n > 0) {
        return 1;
    }

    printf("Enter %d event(s) as: YYYY MM DD HH MM SS\n", n);
    for (int i = 0; i < n; i++) {
        int y, mo, d, h, mi, s;
        if (scanf("%d %d %d %d %d %d", &y, &mo, &d, &h, &mi, &s) != 6) {
            free(events);
            return 1;
        }
        events[i] = dt_pack(y, mo, d, h, mi, s);
    }

    heapsort(events, n);

    printf("In chronological order:\n");
    for (int i = 0; i < n; i++) {
        int y, mo, d, h, mi, s;
        dt_unpack(events[i], &y, &mo, &d, &h, &mi, &s);
        printf("%04d-%02d-%02d %02d:%02d:%02d\n", y, mo, d, h, mi, s);
    }

    free(events);
    return 0;
}
