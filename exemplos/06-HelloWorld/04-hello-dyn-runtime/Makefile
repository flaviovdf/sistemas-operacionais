.PHONY: all clean

all:
	gcc -shared -fPIC printer.c -o libprinter.so
	gcc main-loadtime.c -o main-loadtime ./libprinter.so
	gcc -rdynamic -O2 main-runtime.c -o main-runtime -ldl

clean:
	rm *.so main-loadtime main-runtime
