#include <stdio.h>
#include "poker.h"

/*
 * main.c - the Poker Showdown app (Part 3 in action).
 *
 * Reads a seed, builds a full deck, shuffles it with your deck_shuffle, deals
 * two five-card hands, prints each hand with the category your hand_evaluate
 * finds, and uses hand_compare to announce the winner.
 *
 * You should not need to change this file - it just uses the functions you
 * write in poker.c. Build and run with `make` then `./app`.
 */

static const char *category_name(hand_rank_t r) {
    switch (r) {
        case HAND_HIGH_CARD:      return "High Card";
        case HAND_PAIR:           return "Pair";
        case HAND_TWO_PAIR:       return "Two Pair";
        case HAND_THREE_KIND:     return "Three of a Kind";
        case HAND_STRAIGHT:       return "Straight";
        case HAND_FLUSH:          return "Flush";
        case HAND_FULL_HOUSE:     return "Full House";
        case HAND_FOUR_KIND:      return "Four of a Kind";
        case HAND_STRAIGHT_FLUSH: return "Straight Flush";
    }
    return "?";
}

static void print_hand(const char *who, card_t *hand) {
    hand_sort(hand, HAND_SIZE);
    printf("%s:", who);
    for (int i = 0; i < HAND_SIZE; i++) {
        char buf[4];
        card_to_string(hand[i], buf);
        printf(" %s", buf);
    }
    printf("  ->  %s\n", category_name(hand_evaluate(hand)));
}

int main(void) {
    unsigned int seed;
    printf("Seed? ");
    if (scanf("%u", &seed) != 1) {
        return 1;
    }

    deck_t *deck = deck_create();
    if (deck == NULL) {
        return 1;
    }
    deck_shuffle(deck, seed);

    card_t p1[HAND_SIZE], p2[HAND_SIZE];
    for (int i = 0; i < HAND_SIZE; i++) {
        p1[i] = deck_deal(deck);
    }
    for (int i = 0; i < HAND_SIZE; i++) {
        p2[i] = deck_deal(deck);
    }

    print_hand("Player 1", p1);
    print_hand("Player 2", p2);

    int result = hand_compare(p1, p2);
    if (result > 0) {
        printf("Player 1 wins!\n");
    } else if (result < 0) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a tie!\n");
    }

    deck_free(deck);
    return 0;
}
