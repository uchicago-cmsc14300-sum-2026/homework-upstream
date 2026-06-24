#include "text.h"

/*
 * text.c — IMPLEMENT THE FUNCTIONS BELOW.
 *
 * Rules:
 *   - Do NOT #include <string.h> or <ctype.h>. Build these yourself.
 *   - Treat each string as a char array ending in '\0'.
 *   - Compile cleanly with: -Wall -Wextra -Werror -std=c17
 *
 * Tip: you'll want str_length working first — several other functions can
 * use it. You may also write your own small helper functions in this file.
 */

int str_length(char s[]) {
    /* TODO: Get the length of the string. */
    (void) s;
    return 0;
}

int str_equals(char a[], char b[]) {
    /* TODO: return 1 if a and b are the same string, else 0. */
    (void) a;
    (void) b;
    return 0;
}

void to_upper(char s[]) {
    /* TODO: turn every lowercase letter into uppercase, in place. */
    (void) s;
}

void to_lower(char s[]) {
    /* TODO: turn every uppercase letter into lowercase, in place. */
    (void) s;
}

void reverse(char s[]) {
    /* TODO: reverse s in place (swap from the two ends inward). */
    (void) s;
}

int count_vowels(char s[]) {
    /* TODO: count a/e/i/o/u (either case). */
    (void) s;
    return 0;
}

int count_words(char s[]) {
    /* TODO: count maximal runs of non-whitespace characters. */
    (void) s;
    return 0;
}

int is_palindrome(char s[]) {
    /* TODO: 1 if s reads the same forwards and backwards, else 0.
     * For a challenge: ignore case and non-letter characters. */
    (void) s;
    return 0;
}

void caesar_encrypt(char s[], int shift) {
    /* TODO: shift letters by `shift`, wrapping around the alphabet;
     * preserve case and leave non-letters unchanged. */
    (void) s;
    (void) shift;
}

void caesar_decrypt(char s[], int shift) {
    /* TODO: undo caesar_encrypt with the same shift. */
    (void) s;
    (void) shift;
}
