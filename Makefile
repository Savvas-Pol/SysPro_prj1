all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o list.o hashtable.o BF.o
	gcc vaccineMonitor.o list.o hashtable.o BF.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

list.o: list.c
	gcc -c list.c

hashtable.o: hashtable.c
	gcc -c hashtable.c

BF.o: BF.c
	gcc -c BF.c

clean:
	rm -f vaccineMonitor vaccineMonitor.o list.o hashtable.o BF.o