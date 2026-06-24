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

# Build the Caesar cipher app.
app: text.o main.o
	$(CC) $(CFLAGS) text.o main.o -o app

text.o: text.c text.h
	$(CC) $(CFLAGS) -c text.c

main.o: main.c text.h
	$(CC) $(CFLAGS) -c main.c

# Build and run the public Criterion test suite.
test: text.c text.h test_text.c
	$(CC) $(CFLAGS) text.c test_text.c -o test_text $(CRITERION_FLAGS)
	./test_text --verbose=1

clean:
	rm -f app test_text *.o
