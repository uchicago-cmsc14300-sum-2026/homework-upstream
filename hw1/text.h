#ifndef TEXT_H
#define TEXT_H

/*
 * text.h — your own little string library (CMSC 14300, HW1)
 *
 * A "string" here is a char array terminated by the null character '\0'.
 * None of these functions may use <string.h> or <ctype.h>.
 */

/* Return the number of characters in s, not counting the '\0'. */
int str_length(char s[]);

/* Return 1 if a and b contain the same characters, else 0. */
int str_equals(char a[], char b[]);

/* Convert every lowercase letter in s to uppercase, in place. */
void to_upper(char s[]);

/* Convert every uppercase letter in s to lowercase, in place. */
void to_lower(char s[]);

/* Reverse the characters of s in place. */
void reverse(char s[]);

/* Return how many vowels (a e i o u, upper or lower case) appear in s. */
int count_vowels(char s[]);

/* Return how many words are in s. A word is a maximal run of non-whitespace. */
int count_words(char s[]);

/*
 * Return 1 if s is a palindrome, else 0.
 * Basic version: compare characters exactly.
 * Stretch (extra credit): ignore case and any non-letter characters.
 */
int is_palindrome(char s[]);

/*
 * Shift every letter in s forward by `shift` positions (in place), wrapping
 * around the alphabet. Preserve case; leave non-letters unchanged.
 * `shift` may be larger than 26 or negative.
 */
void caesar_encrypt(char s[], int shift);

/* Undo caesar_encrypt with the same shift (in place). */
void caesar_decrypt(char s[], int shift);

#endif /* TEXT_H */
