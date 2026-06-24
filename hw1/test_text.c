#include <criterion/criterion.h>
#include "text.h"

/*
 * Public sanity tests. These are a SUBSET of the tests used for grading —
 * passing all of these does not guarantee full marks, but failing them means
 * something is clearly wrong. Run with `make test`.
 *
 * Criterion provides its own main(), so there is none here.
 */

Test(str_length, basics) {
    cr_assert_eq(str_length(""), 0);
    cr_assert_eq(str_length("hello"), 5);
    cr_assert_eq(str_length("a b c"), 5);
}

Test(str_equals, basics) {
    cr_assert_eq(str_equals("abc", "abc"), 1);
    cr_assert_eq(str_equals("abc", "abd"), 0);
    cr_assert_eq(str_equals("abc", "ab"), 0);   /* prefix is not equal */
    cr_assert_eq(str_equals("", ""), 1);
}

Test(case, to_upper_and_lower) {
    char a[] = "Hello, World!";
    to_upper(a);
    cr_assert_eq(str_equals(a, "HELLO, WORLD!"), 1);
    to_lower(a);
    cr_assert_eq(str_equals(a, "hello, world!"), 1);
}

Test(reverse, basics) {
    char a[] = "abcde";
    reverse(a);
    cr_assert_eq(str_equals(a, "edcba"), 1);

    char b[] = "";
    reverse(b);
    cr_assert_eq(str_equals(b, ""), 1);
}

Test(count_vowels, basics) {
    cr_assert_eq(count_vowels("aeiou"), 5);
    cr_assert_eq(count_vowels("AEIOU"), 5);
    cr_assert_eq(count_vowels("xyz"), 0);
    cr_assert_eq(count_vowels("Hello World"), 3);
}

Test(count_words, basics) {
    cr_assert_eq(count_words(""), 0);
    cr_assert_eq(count_words("hello"), 1);
    cr_assert_eq(count_words("hello world"), 2);
}

Test(is_palindrome, basic_cases) {
    cr_assert_eq(is_palindrome(""), 1);
    cr_assert_eq(is_palindrome("a"), 1);
    cr_assert_eq(is_palindrome("racecar"), 1);
    cr_assert_eq(is_palindrome("abba"), 1);
    cr_assert_eq(is_palindrome("hello"), 0);
}

Test(caesar, encrypt_decrypt_roundtrip) {
    char a[] = "abc";
    caesar_encrypt(a, 3);
    cr_assert_eq(str_equals(a, "def"), 1);
    caesar_decrypt(a, 3);
    cr_assert_eq(str_equals(a, "abc"), 1);
}

Test(caesar, wraps_around) {
    char a[] = "xyz";
    caesar_encrypt(a, 3);
    cr_assert_eq(str_equals(a, "abc"), 1);
}

Test(caesar, preserves_non_letters_and_case) {
    char a[] = "Hello, World!";
    caesar_encrypt(a, 3);
    cr_assert_eq(str_equals(a, "Khoor, Zruog!"), 1);
}
