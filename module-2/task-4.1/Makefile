all: prog

prog: main.o DoubleListFunc.o PersonFunc.o
	gcc -o prog main.o DoubleListFunc.o PersonFunc.o

main.o: main.c
	gcc -c main.c

DoubleListFunc.o: DoubleListFunc.c
	gcc -c DoubleListFunc.c

PersonFunc.o: PersonFunc.c
	gcc -c PersonFunc.c

clean:
	rm -rf *.o prog
