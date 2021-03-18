all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o help_functions.o list.o hashtable.o BF.o
	gcc vaccineMonitor.o help_functions.o list.o hashtable.o BF.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

help_functions.o: help_functions.c
	gcc -c help_functions.c
	
list.o: list.c
	gcc -c list.c

hashtable.o: hashtable.c
	gcc -c hashtable.c

BF.o: BF.c
	gcc -c BF.c

clean:
	rm -f vaccineMonitor vaccineMonitor.o help_functions.o list.o hashtable.o BF.o
