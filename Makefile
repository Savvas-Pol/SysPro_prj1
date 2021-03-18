all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o
	gcc vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

help_functions.o: help_functions.c
	gcc -c help_functions.c
	
list.o: list.c
	gcc -c list.c
	
skiplist.o: skiplist.c
	gcc -c skiplist.c

hashtable.o: hashtable.c
	gcc -c hashtable.c

BF.o: BF.c
	gcc -c BF.c

date.o: date.c
	gcc -c date.c
	
clean:
	rm -f vaccineMonitor vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o
