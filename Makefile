CC = gcc
CFLAGS = -O3
#CFLAGS = -ggdb -Og -fno-omit-frame-pointer -Wall -pedantic -Werror -std=gnu11 -fsanitize=address -D_GNU_SOURCE
LDFLAGS = -lxdo

all:
	$(CC) $(CFLAGS) -o autohide autohide_main.c $(LDFLAGS)

clean:
	rm -f autohide