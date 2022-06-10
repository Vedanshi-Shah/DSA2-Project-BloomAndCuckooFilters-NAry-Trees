main: main.o naryTree.o hashutil.o cuckoo.o stack.o queue.o
	gcc -o main main.o naryTree.o hashutil.o cuckoo.o stack.o queue.o
main.o: main.c naryTree.h naryTree.c cuckoo.h cuckoo.c hashutil.h hashutil.c
	gcc -c main.c -o main.o
naryTree.o: naryTree.h naryTree.c queue.h queue.c stack.h stack.c cuckoo.h cuckoo.c hashutil.h hashutil.c
	gcc -c naryTree.c -o naryTree.o
hashutil.o: hashutil.h hashutil.c
	gcc -c hashutil.c -o hashutil.o
cuckoo.o: cuckoo.h cuckoo.c
	gcc -c cuckoo.c -o cuckoo.o
stack.o: naryTree.h naryTree.c stack.h stack.c
	gcc -c stack.c -o stack.o
queue.o: naryTree.h naryTree.c queue.h queue.c