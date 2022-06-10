main: main.o naryTree.o queue.o stack.o bitutil.o hashf.o bloom.o
	gcc -o main main.o naryTree.o queue.o stack.o bitutil.o hashf.o bloom.o
main.o: main.c naryTree.h naryTree.c bloom.h bloom.c
	gcc -c main.c -o main.o
naryTree.o: naryTree.c naryTree.h queue.h queue.c stack.h stack.c bloom.h bloom.c
	gcc -c naryTree.c -o naryTree.o
queue.o: queue.c naryTree.h naryTree.c
	gcc -c queue.c -o queue.o
stack.o: naryTree.h naryTree.c stack.h stack.c
	gcc -c stack.c -o stack.o
bitutil.o: bitutil.h bitutil.c
	gcc -c bitutil.c -o bitutil.o
hashf.o: hashf.h hashf.c
	gcc -c hashf.c -o hashf.o
bloom.o: bloom.h bloom.c bitutil.h bitutil.c
	gcc -c bloom.c -o bloom.o

