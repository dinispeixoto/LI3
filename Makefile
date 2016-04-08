CC = gcc 
CFLAGS = -Wall -Wextra -Wunreachable-code -Wunused-parameter -ansi -O2 -Wuninitialized -pedantic
FILES = *.c

default:
	$(CC) $(CFLAGS) $(FILES) -o li3

debug: 
	gcc $(CFLAGS) $(FILES) -g -o debug
	gdb debug

clean:
	rm -f li3
	rm -f debug 