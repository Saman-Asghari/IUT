all: compile

compile: main.o liblibrary.a
		gcc main.o -L./ -llibrary -o app

main.o: main.c
		gcc -c main.c

liblibrary.a: library.o
		ar -r liblibrary.a library.o

library.o: library.c
		gcc -c library.c -o library.o

clean: 
		rm -f *.o *.a app *.img
