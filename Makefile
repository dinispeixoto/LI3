CC = gcc 
CFLAGS = -Wunreachable-code -ansi -O2
FILES = src/*.c

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

# -Wuninitialized -pedantic -Wunused-parameter -Wall -Wextra