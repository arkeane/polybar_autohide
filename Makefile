CC = gcc
CFLAGS = -O3
#CFLAGS = -ggdb -Og -fno-omit-frame-pointer -Wall -pedantic -Werror -std=gnu11 -fsanitize=address -D_GNU_SOURCE
LDFLAGS = -lxdo -lX11
BIN = autohide

all:
	$(CC) $(CFLAGS) -o $(BIN) autohide_main.c $(LDFLAGS)

install: all
	cp $(BIN) /usr/bin/$(BIN)

uninstall:
	rm /usr/bin/$(BIN)

clean:
	rm -f $(BIN)
