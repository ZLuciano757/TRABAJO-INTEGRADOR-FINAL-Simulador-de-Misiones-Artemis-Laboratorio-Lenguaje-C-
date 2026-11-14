CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
OBJETOS = main.o artemis.o validaciones.o

artemis: $(OBJETOS)
	$(CC) $(CFLAGS) -o artemis $(OBJETOS) -lm

main.o: main.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

artemis.o: artemis.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c artemis.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

clean:
	rm -f $(OBJETOS) artemis artemis.exe

.PHONY: clean
