#include <criterion/criterion.h>
#include "poker.h"

/*
 * Public sanity tests. These are a SUBSET of the tests used for grading -
 * passing all of these does not guarantee full marks, but failing them means
 * something is clearly wrong. Run with `make test`.
 *
 * Criterion provides its own main(), so there is none here.
 */

static card_t mk(rank_t r, suit_t s) {
    card_t c = {r, s};
    return c;
}

/* ---- Part 1 - Cards and the deck ---- */

Test(deck_create, fresh_deck) {
    deck_t *d = deck_create();
    cr_assert_not_null(d, "deck_create should allocate");
    cr_assert_eq(d->size, 52, "a fresh deck has 52 cards");
    cr_assert_eq(d->capacity, 52);
    cr_assert(d->cards[0].rank == RANK_TWO && d->cards[0].suit == SUIT_CLUBS,
              "index 0 is the two of clubs");
    cr_assert(d->cards[51].rank == RANK_ACE && d->cards[51].suit == SUIT_SPADES,
              "index 51 is the ace of spades");
    deck_free(d);
}

Test(card_to_string, formats) {
    char buf[4];
    card_to_string(mk(RANK_ACE, SUIT_SPADES), buf);
    cr_assert_str_eq(buf, "AS");
    card_to_string(mk(RANK_TEN, SUIT_HEARTS), buf);
    cr_assert_str_eq(buf, "10H");
    card_to_string(mk(RANK_TWO, SUIT_CLUBS), buf);
    cr_assert_str_eq(buf, "2C");
}

Test(deck_deal, from_top) {
    deck_t *d = deck_create();
    cr_assert_not_null(d);
    card_t top = deck_deal(d);
    cr_assert(top.rank == RANK_ACE && top.suit == SUIT_SPADES,
              "the top card is the ace of spades");
    cr_assert_eq(d->size, 51, "dealing decreases size");
    deck_free(d);
}

/* ---- Part 2 - Shuffle and sort ---- */

Test(deck_shuffle, deterministic) {
    deck_t *d = deck_create();
    cr_assert_not_null(d);
    deck_shuffle(d, 42);
    /* The pinned generator fixes the whole order for seed 42. */
    cr_assert(d->cards[0].rank == RANK_SIX && d->cards[0].suit == SUIT_CLUBS,
              "seed 42 puts the six of clubs at index 0");
    cr_assert(d->cards[1].rank == RANK_FIVE && d->cards[1].suit == SUIT_SPADES,
              "seed 42 puts the five of spades at index 1");
    cr_assert_eq(d->size, 52, "shuffling does not lose cards");
    deck_free(d);
}

Test(hand_sort, descending_with_suit_tiebreak) {
    card_t h[] = {
        mk(RANK_KING, SUIT_HEARTS), mk(RANK_KING, SUIT_SPADES),
        mk(RANK_SEVEN, SUIT_CLUBS), mk(RANK_FIVE, SUIT_CLUBS),
        mk(RANK_TWO, SUIT_DIAMONDS),
    };
    hand_sort(h, 5);
    cr_assert(h[0].rank == RANK_KING && h[0].suit == SUIT_SPADES,
              "higher suit of the two kings comes first");
    cr_assert(h[1].rank == RANK_KING && h[1].suit == SUIT_HEARTS);
    for (int i = 1; i < 5; i++) {
        cr_assert(h[i - 1].rank >= h[i].rank, "ranks are descending at %d", i);
    }
}

/* ---- Part 3 - Evaluate and compare ---- */

Test(hand_evaluate, categories) {
    card_t full_house[] = {
        mk(RANK_ACE, SUIT_CLUBS), mk(RANK_ACE, SUIT_DIAMONDS),
        mk(RANK_ACE, SUIT_HEARTS), mk(RANK_KING, SUIT_CLUBS),
        mk(RANK_KING, SUIT_DIAMONDS),
    };
    cr_assert_eq(hand_evaluate(full_house), HAND_FULL_HOUSE);

    card_t flush[] = {
        mk(RANK_TWO, SUIT_HEARTS), mk(RANK_FIVE, SUIT_HEARTS),
        mk(RANK_NINE, SUIT_HEARTS), mk(RANK_JACK, SUIT_HEARTS),
        mk(RANK_KING, SUIT_HEARTS),
    };
    cr_assert_eq(hand_evaluate(flush), HAND_FLUSH);

    card_t straight[] = {
        mk(RANK_FIVE, SUIT_CLUBS), mk(RANK_SIX, SUIT_DIAMONDS),
        mk(RANK_SEVEN, SUIT_HEARTS), mk(RANK_EIGHT, SUIT_SPADES),
        mk(RANK_NINE, SUIT_CLUBS),
    };
    cr_assert_eq(hand_evaluate(straight), HAND_STRAIGHT);

    card_t wheel[] = {
        mk(RANK_ACE, SUIT_CLUBS), mk(RANK_TWO, SUIT_DIAMONDS),
        mk(RANK_THREE, SUIT_HEARTS), mk(RANK_FOUR, SUIT_SPADES),
        mk(RANK_FIVE, SUIT_CLUBS),
    };
    cr_assert_eq(hand_evaluate(wheel), HAND_STRAIGHT, "the wheel is a straight");
}

Test(hand_compare, basics) {
    card_t pair_aces[] = {
        mk(RANK_ACE, SUIT_CLUBS), mk(RANK_ACE, SUIT_DIAMONDS),
        mk(RANK_THREE, SUIT_HEARTS), mk(RANK_FOUR, SUIT_SPADES),
        mk(RANK_FIVE, SUIT_CLUBS),
    };
    card_t pair_kings[] = {
        mk(RANK_KING, SUIT_CLUBS), mk(RANK_KING, SUIT_DIAMONDS),
        mk(RANK_THREE, SUIT_HEARTS), mk(RANK_FOUR, SUIT_SPADES),
        mk(RANK_FIVE, SUIT_CLUBS),
    };
    cr_assert(hand_compare(pair_aces, pair_kings) > 0, "aces beat kings");
    cr_assert(hand_compare(pair_kings, pair_aces) < 0, "and the reverse");

    card_t six_high[] = {
        mk(RANK_TWO, SUIT_CLUBS), mk(RANK_THREE, SUIT_DIAMONDS),
        mk(RANK_FOUR, SUIT_HEARTS), mk(RANK_FIVE, SUIT_SPADES),
        mk(RANK_SIX, SUIT_CLUBS),
    };
    card_t wheel[] = {
        mk(RANK_ACE, SUIT_CLUBS), mk(RANK_TWO, SUIT_DIAMONDS),
        mk(RANK_THREE, SUIT_HEARTS), mk(RANK_FOUR, SUIT_SPADES),
        mk(RANK_FIVE, SUIT_HEARTS),
    };
    cr_assert(hand_compare(six_high, wheel) > 0,
              "a six-high straight beats the five-high wheel");
}
