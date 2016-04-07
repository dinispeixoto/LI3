CC = gcc 
CFLAGS = -Wall -Wextra -Wunreachable-code -Wunused-parameter -ansi
FILES = $(wildcard *.c)

default:
	$(CC) $(CFLAGS) $(FILES) -o gereVendas 

debug: 
	gcc $(CFLAGS) -g -o debug
	gdb debug

clean:
	rm gereVendas 