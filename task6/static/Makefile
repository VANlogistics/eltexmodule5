

all: main.o f1.o f2.o
	gcc main.o f1.o f2.o -o rezult

fs: f2.o f1.o
	gcc -c f2.c f1.c
	ar rc libfs.a f1.o f2.o

mainfs: main.o
	gcc main.o -L. -lfs -o rezult2

main.o: main.c
	gcc -c main.c

f1.o: f1.c
	gcc -c f1.c

f2.o: f2.c
	gcc -c f2.c

clean:
	rm *.o
	rm rezult
	rm rezult2
	rm libfs.a





