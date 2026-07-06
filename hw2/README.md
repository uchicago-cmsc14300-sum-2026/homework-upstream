# HW2 - Event Log Sorter

This is the starter code. Implement the functions in **`events.c`** (their
contract is documented in `events.h`), then build and test.

## Files

| File | What it is |
|------|------------|
| `events.h` | The function declarations + spec, including the datetime bit layout. **Do not change.** |
| `events.c` | **You edit this** - fill in the function bodies. |
| `main.c` | The Event Log Sorter app that uses your functions. No changes needed. |
| `test_events.c` | Public sanity tests (a subset of the grading tests). |
| `Makefile` | Build rules. |

## Building and running

```bash
make          # builds the app
./app         # run the sorter: type a count, then that many timestamps

make test     # build and run the public Criterion test suite
make try      # build a scratch driver you write (try.c) to call one function
make clean    # remove built files
```

To debug a single function instead of the whole app, create your own `try.c`
here with a `main()` that calls the `events.c` functions you want to test, then
run `make try && ./try`. It is not submitted and the grader never builds it, so
`make try` simply fails until you create the file. See the "Trying one function
at a time" section in `../hw2.md` for a starting example.

Example run:

```
$ ./app
How many events? 3
Enter 3 event(s) as: YYYY MM DD HH MM SS
2026 07 15 09 30 00
2024 01 01 00 00 00
2026 07 15 09 29 59
In chronological order:
2024-01-01 00:00:00
2026-07-15 09:29:59
2026-07-15 09:30:00
```

## Rules

- Do **not** use `qsort`. Build the heap and the sort yourself.
- Your code must compile cleanly with `-Wall -Wextra -Werror -std=c17` (the
  Makefile already uses these flags).
- Every `malloc`/`realloc` must have a matching `free`. Check with
  `valgrind ./app` and `valgrind ./test_events`.

See `../hw2.md` for the full assignment, grading breakdown, and submission
instructions.
