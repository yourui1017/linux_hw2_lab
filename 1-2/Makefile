CC = gcc
CFLAGS = -O1 -g -Wall -Werror -Idudect -I.

CFILES = main.c timsort.c

main: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main
