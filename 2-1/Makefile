CC = gcc
CFLAGS = -O1 -g -Wall -Werror -I.

CFILES = main.c tree.c

main: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main
