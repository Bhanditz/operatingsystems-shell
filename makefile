all: minish
asdf
minish: minish.o
	gcc minish.o -o minish

minish.o: minish.c
	gcc -c -g minish.c -o minish.o

clean:
	-rm minish.o minish.c
