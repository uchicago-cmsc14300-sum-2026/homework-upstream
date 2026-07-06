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

# Build the Event Log Sorter app.
app: events.o main.o
	$(CC) $(CFLAGS) events.o main.o -o app

events.o: events.c events.h
	$(CC) $(CFLAGS) -c events.c

main.o: main.c events.h
	$(CC) $(CFLAGS) -c main.c

# Build and run the public Criterion test suite.
test: events.c events.h test_events.c
	$(CC) $(CFLAGS) events.c test_events.c -o test_events $(CRITERION_FLAGS)
	./test_events --verbose=1

# Build a scratch driver for calling individual functions by hand. You write
# try.c yourself (see the handout); it just needs its own main() that calls the
# events.c functions you want to exercise. Then: make try && ./try
try: events.c events.h try.c
	$(CC) $(CFLAGS) events.c try.c -o try

clean:
	rm -f app test_events try *.o
