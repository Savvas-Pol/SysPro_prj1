all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o commands.o citizen.o
	gcc vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o commands.o citizen.o -o vaccineMonitor

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
	
commands.o: commands.c
	gcc -c commands.c
	
citizen.o: citizen.c
	gcc -c citizen.c
	
clean:
	rm -f vaccineMonitor vaccineMonitor.o help_functions.o list.o skiplist.o hashtable.o BF.o date.o commands.o citizen.o
