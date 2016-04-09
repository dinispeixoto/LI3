CC = gcc 
CFLAGS = -Wall -Wextra -Wunreachable-code -Wunused-parameter -ansi -O2 -Wuninitialized -pedantic
FILES = *.c

default:
	$(CC) $(CFLAGS) $(FILES) -o gereVendas

run:
	$(CC) $(CFLAGS) $(FILES) -o gereVendas
	./gereVendas

debug: 
	gcc $(CFLAGS) $(FILES) -g -o debug
	gdb debug

clean:
	rm -f gereVendas
	rm -f debug 