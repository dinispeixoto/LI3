CC = gcc 

CFLAGS = -ansi -Wunreachable-code -O2 -Wuninitialized -Wunused-parameter -Wall -Wextra 

OBJECTS = obj/main.o obj/avl.o obj/CatClients.o obj/CatProducts.o obj/facturacao.o \
		  obj/filial.o obj/heap.o obj/interpretador.o obj/listaStrings.o \
		  obj/queries.o obj/readFiles.o obj/Sales.o 

DOC = doc/Doxyfile

compile: $(OBJECTS)
	$(CC) $(CFLAGS) -o gereVendas $(OBJECTS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<	

obj/main.o: src/headers/CatClients.h src/headers/CatProducts.h src/headers/facturacao.h \
			src/headers/interpretador.h src/headers/filial.h
obj/avl.o: src/headers/avl.h 
obj/CatClients.o: src/headers/CatClients.h src/headers/avl.h
obj/CatProducts.o: src/headers/CatProducts.h src/headers/avl.h	
obj/facturacao.o: src/headers/facturacao.h src/headers/Sales.h src/headers/avl.h
obj/filial.o: src/headers/filial.h src/headers/avl.h src/headers/CatClients.h \
			  src/headers/CatProducts.h src/headers/Sales.h
obj/heap.o: src/headers/heap.h 
obj/interpretador.o: src/headers/interpretador.h src/headers/CatClients.h src/headers/CatProducts.h \
					 src/headers/filial.h src/headers/facturacao.h src/headers/readFiles.h \
					 src/headers/queries.h src/headers/listaStrings.h
obj/listaStrings.o: src/headers/listaStrings.h 
obj/queries.o: src/headers/queries.h src/headers/facturacao.h src/headers/filial.h src/headers/heap.h \
			   src/headers/listaStrings.h 
obj/readFiles.o: src/headers/readFiles.h src/headers/CatClients.h src/headers/CatProducts.h \
				 src/headers/facturacao.h src/headers/filial.h
obj/Sales.o: src/headers/Sales.h src/headers/CatClients.h src/headers/CatProducts.h


run: $(OBJECTS)
	$(CC) $(CFLAGS) -o gereVendas $(OBJECTS)
	./gereVendas

clean:
	rm -f gereVendas
	rm -f debug 
	rm -f $(OBJECTS)

debug: $(OBJECTS)
	$(CC) $(OBJECTS) -g -o debug
	gdb debug

.PHONY: doc
doc:$(OBJECTS)
		doxygen $(DOC)

#  -pedantic -Wunused-parameter -Wall -Wextra 