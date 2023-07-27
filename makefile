#executable
run: utf-8.o prog.o
	gcc -Wall -o run prog.o utf-8.o -O2
	rm -f *.o



#example program
prog.o: src/prog.c lib/utf-8.h
	gcc -Wall -c src/prog.c -O2

#utf-8 library
utf-8.o: lib/utf-8.c lib/utf-8.h
	gcc -Wall -c lib/utf-8.c -O2
