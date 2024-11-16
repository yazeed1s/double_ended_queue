CC = gcc
CFLAGS = -Wall -Wextra -g

all: test

test: test.o deque.o
	$(CC) $(CFLAGS) -o test test.o deque.o

test.o: test.c deque.h
	$(CC) $(CFLAGS) -c test.c

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c

clean:
	rm -f test *.o

.PHONY: all clean
