#include <stdlib.h>
#include "poker.h"

/*
 * poker.c - IMPLEMENT THE FUNCTIONS BELOW.
 *
 * Rules:
 *   - Do NOT use qsort. Write the ordering logic yourself.
 *   - Compile cleanly with: -Wall -Wextra -Werror -std=c17
 *   - Every malloc you make must have a matching free (deck_free frees what
 *     deck_create allocated). Run valgrind to check for leaks.
 *
 * You may add your own static helper functions in this file (a swap and a
 * hand-scoring helper are natural ones). The (void) lines below just silence
 * "unused parameter" warnings in the stubs; delete them as you implement.
 */

/* ---- Part 1 - Cards and the deck ---- */

deck_t *deck_create(void) {
    /* TODO: malloc a deck_t and its 52-card array, fill the cards in order
     * (see poker.h), set size and
     * capacity to 52. Return NULL if either allocation fails. Replace the code
     * below with your implementation. 
     * HINT: Enums are integers, you may use that fact to systematically 
     * build the deck. */
    return NULL;
}

void deck_free(deck_t *d) {
    /* TODO: free the cards array, then the deck_t. free(NULL) is fine.
     * Replace the code below with your implementation. */
    (void) d;
}

card_t deck_deal(deck_t *d) {
    /* TODO: decrease size and return the card that was on top (index size - 1).
     * Assume size > 0. Replace the code below with your implementation. */
    (void) d;
    card_t c = {RANK_TWO, SUIT_CLUBS};
    return c;
}

void card_to_string(card_t c, char *buf) {
    /* TODO: write the rank (2..9, "10", J, Q, K, A) then the suit letter
     * (C, D, H, S) into buf, ending with '\0'. Replace the code below with your
     * implementation. */
    (void) c;
    buf[0] = '\0';
}

/* ---- Part 2 - Shuffle and sort ---- */

void deck_shuffle(deck_t *d, unsigned int seed) {
    /* TODO: Fisher-Yates over indices size-1 down to 1, using EXACTLY the
     * generator described in poker.h (advance state, then read bits) so your
     * shuffle matches the reference. Replace the code below with your
     * implementation. */
    (void) d;
    (void) seed;
}

void hand_sort(card_t *hand, int n) {
    /* TODO: sort n cards descending by rank, breaking ties by higher suit.
     * Do not use qsort. Replace the code below with your implementation. */
    (void) hand;
    (void) n;
}

/* ---- Part 3 - Evaluate and compare ---- */

hand_rank_t hand_evaluate(const card_t *hand) {
    /* TODO: return the best category the five cards form (see poker.h, including
     * the straight and wheel rules). Replace the code below with your
     * implementation. */
    (void) hand;
    return HAND_HIGH_CARD;
}

int hand_compare(const card_t *a, const card_t *b) {
    /* TODO: return >0 if a wins, <0 if b wins, 0 on a tie. Compare categories
     * first, then the tie-breakers in poker.h. Replace the code below with your
     * implementation. */
    (void) a;
    (void) b;
    return 0;
}
