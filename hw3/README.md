# HW3 - Poker Hand Evaluator

This is the starter code. Implement the functions in **`poker.c`** (their
contract is documented in `poker.h`), then build and test.

## Files

| File | What it is |
|------|------------|
| `poker.h` | The function declarations + spec, including the card model, the shuffle generator, and the hand-ranking rules. **Do not change.** |
| `poker.c` | **You edit this** - fill in the function bodies. |
| `main.c` | The Poker Showdown app that uses your functions. No changes needed. |
| `test_poker.c` | Public sanity tests (a subset of the grading tests). |
| `Makefile` | Build rules. |

## Building and running

```bash
make          # builds the app
./app         # run the showdown: type a seed, see two hands and the winner

make test     # build and run the public Criterion test suite
make try      # build a scratch driver you write (try.c) to call one function
make clean    # remove built files
```

To debug a single function instead of the whole app, create your own `try.c`
here with a `main()` that calls the `poker.c` functions you want to test, then
run `make try && ./try`. It is not submitted and the grader never builds it, so
`make try` simply fails until you create the file. See the "Trying one function
at a time" section in `../hw3.md` for a starting example.

Example run:

```
$ ./app
Seed? 42
Player 1: KS QS 8H 8D 6H  ->  Pair
Player 2: AC 9H 4D 3S 3C  ->  Pair
Player 1 wins!
```

## Rules

- Do **not** use `qsort`. Write the ordering logic yourself.
- Your code must compile cleanly with `-Wall -Wextra -Werror -std=c17` (the
  Makefile already uses these flags).
- Every `malloc` must have a matching `free`. Check with `valgrind ./app` and
  `valgrind ./test_poker`.

See `../hw3.md` for the full assignment, grading breakdown, and submission
instructions.
