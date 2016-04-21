CC = gcc 
CFLAGS = -Wunreachable-code -ansi -O2 -Wuninitialized -Wunused-parameter -Wall
FILES = src/*.c

default:
	$(CC) $(CFLAGS) $(FILES) -o gereVendas

run:
	$(CC) $(CFLAGS) $(FILES) -o gereVendas
	./gereVendas

clean:
	rm -f gereVendas
	rm -f debug 

debug: 
	gcc $(FILES) -g -o debug
	gdb debug


#  -pedantic -Wunused-parameter -Wall -Wextra 