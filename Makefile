CC = gcc 
CFLAGS = -Wunreachable-code -Wunused-parameter -ansi -O2
FILES = $(wildcard *.h *.c)

default:
	$(CC) $(CFLAGS) $(FILES) -o li3

debug: 
	gcc $(CFLAGS) $(FILES) -g -o debug
	gdb debug

clean:
	rm li3 