

all: main.o f1.o f2.o
	gcc main.o f1.o f2.o -o rezult

dfs: 
	gcc -fPIC -c f2.c
	gcc -fPIC -c f1.c

maindfs: main.o
	gcc main.o -L. -lfsdyn -o rezultdyn

main.o: main.c
	gcc -c main.c

f1.o: f1.c
	gcc -c f1.c

f2.o: f2.c
	gcc -c f2.c

clean:
	rm *.so
	rm *.o
	rm rezult
	rm rezultdyn






