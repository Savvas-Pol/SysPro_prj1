all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o help_functions.o skiplist.o hashtable_virus.o hashtable_citizen.o hashtable_country.o BF.o date.o commands.o citizen.o
	gcc vaccineMonitor.o help_functions.o skiplist.o hashtable_virus.o hashtable_citizen.o hashtable_country.o BF.o date.o commands.o citizen.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

help_functions.o: help_functions.c
	gcc -c help_functions.c
	
skiplist.o: skiplist.c
	gcc -c skiplist.c

hashtable_virus.o: hashtable_virus.c
	gcc -c hashtable_virus.c

hashtable_citizen.o: hashtable_citizen.c
	gcc -c hashtable_citizen.c

hashtable_country.o: hashtable_country.c
	gcc -c hashtable_country.c
	
BF.o: BF.c
	gcc -c BF.c

date.o: date.c
	gcc -c date.c
	
commands.o: commands.c
	gcc -c commands.c
	
citizen.o: citizen.c
	gcc -c citizen.c
	
clean:
	rm -f vaccineMonitor vaccineMonitor.o help_functions.o skiplist.o hashtable_virus.o hashtable_citizen.o hashtable_country.o BF.o date.o commands.o citizen.o
