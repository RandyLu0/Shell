all: shell.o main.o
	gcc -o program shell.o main.o
shell.o: shell.c shell.h
	gcc -c shell.c
main.o: main.c shell.h
	gcc -c main.c
run:
	./program
