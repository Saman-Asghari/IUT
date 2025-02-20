all:saman_app

install:saman_app
	sudo cp p /usr/bin/p

uninstall:
	sudo rm /usr/bin/p


saman_app:prime.o main.o
	gcc prime.o main.o -o p

prime.o:prime.c
	gcc -c prime.c

main.o:main.c
	gcc -c main.c	


clean:
	rm -rf prime.o main.o p