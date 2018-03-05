all:
	gcc -Wall load.c -o load
	objdump -d load > load.dump
	gcc -Wall -Ttext=0x800000 load.c -o load8
	objdump -d load8 > load8.dump
	gcc -Wall -Ttext=0xFF00 load.c -o loadbios
	objdump -d loadbios > loadbios.dump

clean:
	rm -f load load8 loadbios
	rm -f load.dump load8.dump loadbios.dump

