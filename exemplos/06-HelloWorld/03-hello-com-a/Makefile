.PHONY: all clean

all:
	gcc -c printer.c somador.c
	ar rcs libflavio.a printer.o somador.o
	gcc -O2 -c main.c
	gcc -static main.o -o main ./libflavio.a

clean:
	rm *.a *.o main
