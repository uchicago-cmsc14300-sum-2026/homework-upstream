#ifndef POKER_H
#define POKER_H

/*
 * poker.h - Poker Hand Evaluator (CMSC 14300, HW3)
 *
 * This is the first homework built around structs and pointers to structs.
 * You will model a deck of playing cards with structs, deal and shuffle a deck
 * that lives on the heap, and then evaluate and compare five-card poker hands.
 *
 *   Part 1 - the card and deck model: a `card_t` struct, and a `deck_t` that
 *            OWNS a 52-card array you allocate on the heap yourself,
 *   Part 2 - shuffling a deck in place and sorting a hand of cards, and
 *   Part 3 - evaluating a five-card hand into a category and comparing two
 *            hands to decide which one wins.
 *
 * A pre-written main.c ("the showdown") uses your functions to deal two hands
 * from a shuffled deck and announce the winner.
 *
 * You may NOT use qsort (from <stdlib.h>) anywhere - the point is to write the
 * ordering logic yourself.
 */

/* ===========================================================================
 * The card model
 *
 * A card has a rank and a suit. Ranks are numbered so that a larger enum value
 * is a higher card: the ace is high (14). Suits are ordered clubs < diamonds <
 * hearts < spades; that order is only used as a tie-breaker when sorting a hand,
 * never to decide which poker hand wins (suits do not break ties in poker).
 * ========================================================================= */

typedef enum {
    RANK_TWO = 2, RANK_THREE, RANK_FOUR, RANK_FIVE, RANK_SIX, RANK_SEVEN,
    RANK_EIGHT, RANK_NINE, RANK_TEN, RANK_JACK, RANK_QUEEN, RANK_KING, RANK_ACE
} rank_t;                                   /* the numeric values run 2 .. 14  */

typedef enum {
    SUIT_CLUBS, SUIT_DIAMONDS, SUIT_HEARTS, SUIT_SPADES
} suit_t;                                   /* the numeric values run 0 .. 3   */

typedef struct {
    rank_t rank;
    suit_t suit;
} card_t;

/*
 * A deck owns its cards. `cards` points at a heap array of `capacity` cards
 * (always 52 for a full deck); `size` is how many cards are still in the deck.
 * Dealing a card removes it from the top and decreases `size`.
 */
typedef struct {
    card_t *cards;                          /* heap-owned array of cards       */
    int size;                               /* cards remaining in the deck     */
    int capacity;                           /* total slots allocated (52)      */
} deck_t;

#define DECK_SIZE 52                        /* cards in a full deck            */
#define HAND_SIZE 5                         /* cards in a poker hand           */

/*
 * A hand is ranked into one of these nine categories. They are ordered from
 * weakest (HAND_HIGH_CARD == 0) to strongest (HAND_STRAIGHT_FLUSH == 8), so a
 * larger category value always beats a smaller one.
 */
typedef enum {
    HAND_HIGH_CARD = 0,
    HAND_PAIR,
    HAND_TWO_PAIR,
    HAND_THREE_KIND,
    HAND_STRAIGHT,
    HAND_FLUSH,
    HAND_FULL_HOUSE,
    HAND_FOUR_KIND,
    HAND_STRAIGHT_FLUSH
} hand_rank_t;

/* ===========================================================================
 * Part 1 - Cards and the deck
 * ========================================================================= */

/*
 * Allocate a full 52-card deck on the heap and return a pointer to it. Both the
 * deck_t struct AND its `cards` array are allocated with malloc; the caller owns
 * the result and must later pass it to deck_free. Return NULL if either
 * allocation fails.
 *
 * The deck starts full and in this exact order (suit by suit, low rank to high):
 *
 *     index 0  = 2 of clubs, 1 = 3 of clubs, ... , 12 = ace of clubs,
 *     index 13 = 2 of diamonds, ... , 25 = ace of diamonds,
 *     index 26 = 2 of hearts, ... , 38 = ace of hearts,
 *     index 39 = 2 of spades, ... , 51 = ace of spades.
 *
 * Failure to start the deck in this order will cause tests to fail.
 */
deck_t *deck_create(void);

/*
 * Free a deck returned by deck_create: free the `cards` array, then the deck_t
 * itself. Passing NULL is allowed and does nothing.
 */
void deck_free(deck_t *d);

/*
 * Remove and return the top card of the deck - the card at index size - 1 -
 * and decrease size by one. You may assume the deck is not empty (size > 0).
 */
card_t deck_deal(deck_t *d);

/*
 * Write a short text form of a card into `buf`, followed by a '\0'. The rank
 * comes first, then a one-letter suit (C, D, H, S):
 *
 *     ranks 2..9 -> "2".."9",  10 -> "10",  J, Q, K, A
 *     suits       -> clubs 'C', diamonds 'D', hearts 'H', spades 'S'
 *
 * Examples: the ace of spades -> "AS", the ten of hearts -> "10H", the two of
 * clubs -> "2C". `buf` must be at least 4 bytes (the longest form, "10H", plus
 * the terminator).
 */
void card_to_string(card_t c, char *buf);

/* ===========================================================================
 * Part 2 - Shuffle and sort
 * ========================================================================= */

/*
 * Shuffle the cards currently in the deck (indices 0 .. size - 1) in place,
 * using the Fisher-Yates algorithm driven by a small pseudo-random generator so
 * that the result is fully determined by `seed`. Use EXACTLY this generator, so
 * your shuffle matches the reference and the demo:
 *
 *     Keep a 32-bit unsigned state, starting at `seed`. Each time you need a
 *     random number, first advance the state and then read the middle bits:
 *
 *         state = state * 1103515245u + 12345u;   // advance
 *         r = (state >> 16) & 0x7fffu;            // r is in [0, 32767]
 *
 * Walk i from size - 1 down to 1. For each i, draw one r as above and let
 * j = r % (i + 1); then swap cards[i] and cards[j]. Drawing exactly one random
 * number per step, in this order, is what makes your deck match the grader's.
 */
void deck_shuffle(deck_t *d, unsigned int seed);

/*
 * Sort the array of n cards in place into descending order: highest rank first.
 * Break ties between equal ranks by suit, higher suit first (spades before
 * hearts before diamonds before clubs). Do NOT use qsort; write the sort
 * yourself (n is small - a simple sort is fine).
 */
void hand_sort(card_t *hand, int n);

/* ===========================================================================
 * Part 3 - Evaluate and compare
 *
 * Every hand passed to these functions has exactly HAND_SIZE (5) cards. The
 * cards may be in any order.
 *
 * Straights: five cards of consecutive rank. Because the ace is high, the
 * highest straight is 10-J-Q-K-A. The one special case is the "wheel",
 * A-2-3-4-5, which counts as a straight whose high card is the five (so it is
 * the LOWEST straight, beaten by 2-3-4-5-6). The ace is high everywhere else.
 * ========================================================================= */

/*
 * Return the best category the five cards form, as one of the hand_rank_t values
 * above (the highest category that applies).
 */
hand_rank_t hand_evaluate(const card_t *hand);

/*
 * Compare two five-card hands. Return a positive number if hand `a` wins, a
 * negative number if hand `b` wins, and 0 if they tie. First the categories are
 * compared; if they are equal, the standard poker tie-breakers decide it:
 *
 *   - straight / straight flush: the higher top card of the run wins (the wheel
 *     counts as five-high),
 *   - four of a kind: higher four, then the kicker,
 *   - full house: higher three-of-a-kind, then the pair,
 *   - flush / high card: compare cards from highest down until they differ,
 *   - three of a kind: the triple, then the remaining cards high to low,
 *   - two pair: the higher pair, then the lower pair, then the kicker,
 *   - one pair: the pair, then the remaining cards high to low.
 *
 * Suits never break a tie: two hands can tie (return 0). The pointers are const
 * because comparing must not modify either hand.
 */
int hand_compare(const card_t *a, const card_t *b);

#endif /* POKER_H */
