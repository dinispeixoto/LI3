CFLAGS= -Wall -Wextra -ansi -pedantic -O2
OBJS=$(patsubst %.c,$(wildcard *.c))

prot:$(OBJS)
		$(CC) $(CFLAGS) -o GereVendas $(OBJS) $(LIBS)

doc:$(OBJS)
		doxygen

limpar:
	rm prot *.o

remover:
	rm -r html
	rm -r latex
