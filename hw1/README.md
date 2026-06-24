# HW1 - Build Your Own String Library

This is the starter code. Implement the functions in **`text.c`** (their contract
is documented in `text.h`), then build and test.

## Files

| File | What it is |
|------|------------|
| `text.h` | The function declarations + spec. **Do not change.** |
| `text.c` | **You edit this** - fill in the function bodies. |
| `main.c` | The Caesar cipher app that uses your functions. No changes needed. |
| `test_text.c` | Public sanity tests (a subset of the grading tests). |
| `Makefile` | Build rules. |

## Building and running

```bash
make          # builds the app
./app         # run the Caesar cipher: type a line, then a shift

make test     # build and run the public Criterion test suite
make clean    # remove built files
```

## Rules

- Do **not** `#include <string.h>` or `<ctype.h>` - the point is to build these
  yourself.
- Your code must compile cleanly with `-Wall -Wextra -Werror -std=c17` (the
  Makefile already uses these flags).
- No pointers required; treat strings as `char` arrays ending in `'\0'`.