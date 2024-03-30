CC = gcc
CFLAGS = -O1 -g -Wall -Werror -Idudect -I.

CFILES = main.c qsort.c random.c

main: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main
