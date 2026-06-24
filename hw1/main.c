#include <stdio.h>
#include "text.h"

/*
 * main.c — the Caesar cipher app (Part 3).
 *
 * Reads a line of text and a shift, prints the encrypted text, then decrypts
 * it again to show the round-trip. Build and run with `make` then `./app`.
 *
 * You should not need to change this file — it just uses the functions you
 * write in text.c.
 */

int main(void) {
    char line[256];
    int shift;

    printf("Enter a line of text: ");
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    /* fgets keeps the trailing newline; drop it so it doesn't print on its own line */
    int n = str_length(line);
    if (n > 0 && line[n - 1] == '\n') {
        line[n - 1] = '\0';
    }

    printf("Enter a shift: ");
    if (scanf("%d", &shift) != 1) {
        return 1;
    }

    caesar_encrypt(line, shift);
    printf("Encrypted: %s\n", line);

    caesar_decrypt(line, shift);
    printf("Decrypted: %s\n", line);

    return 0;
}
