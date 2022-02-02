CC=gcc
CFLAGS=-O3 
#CFLAGS=-ggdb -Og -fno-omit-frame-pointer -Wall -pedantic -Werror -std=gnu11 -fsanitize=address -D_GNU_SOURCE

all: autohide

autohide: autohide.o
	$(CC) $(CFLAGS) -o $@ $^ -lxdo

clean:
	rm -f autohide.o

purge:
	rm -f autohide.o 
	rm -f autohide

.PHONY: clean
