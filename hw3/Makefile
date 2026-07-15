CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c17

# Criterion: if Homebrew is present (macOS, or Linuxbrew), add its include/lib
# paths since they aren't searched by default. Otherwise rely on system paths
# (e.g. apt installs into /usr/include and /usr/lib).
BREW_PREFIX = $(shell brew --prefix 2>/dev/null)
ifneq ($(BREW_PREFIX),)
CRITERION_FLAGS = -I$(BREW_PREFIX)/include -L$(BREW_PREFIX)/lib -lcriterion
else
CRITERION_FLAGS = -lcriterion
endif

# Build the Poker Showdown app.
app: poker.o main.o
	$(CC) $(CFLAGS) poker.o main.o -o app

poker.o: poker.c poker.h
	$(CC) $(CFLAGS) -c poker.c

main.o: main.c poker.h
	$(CC) $(CFLAGS) -c main.c

# Build and run the public Criterion test suite.
test: poker.c poker.h test_poker.c
	$(CC) $(CFLAGS) poker.c test_poker.c -o test_poker $(CRITERION_FLAGS)
	./test_poker --verbose=1

# Build a scratch driver for calling individual functions by hand. You write
# try.c yourself (see the handout); it just needs its own main() that calls the
# poker.c functions you want to exercise. Then: make try && ./try
try: poker.c poker.h try.c
	$(CC) $(CFLAGS) poker.c try.c -o try

clean:
	rm -f app test_poker try *.o
