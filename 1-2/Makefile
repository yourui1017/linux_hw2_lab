CC = gcc
CFLAGS = -O1 -g -Wall -Werror -I.

CFILES = main.c timsort.c insertion_sort.c

main: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main
