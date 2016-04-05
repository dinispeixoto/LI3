CC = gcc 
CFLAGS = -Wall -Wextra -Wunreachable-code -Wunused-parameter -ansi
FILES = $(wildcard *.h *.c)

default:
	$(CC) $(CFLAGS) $(FILES) -o li3

debug: 
	gcc $(CFLAGS) -g -o debug
	gdb debug

clean:
	rm li3 