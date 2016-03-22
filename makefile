CC = gcc 
CFLAGS = -Wall -Wextra
FILES = main.c valida.c testes.c avl.c CatProducts.c CatClients.c

default: 
	$(CC) $(CFLAGS) $(FILES) -o li3

debug: 
	gcc *.c -g -o debug
	gdb debug

clean:
	rm li3 
