all: shell.o
	gcc -o program shell.o
shell.o:
	gcc -c shell.c
run:
	./program
