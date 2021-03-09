all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o list.o BF.o
	gcc vaccineMonitor.o list.o BF.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

list.o: list.c
	gcc -c list.c

BF.o: BF.c
	gcc -c BF.c

clean:
	rm -f vaccineMonitor vaccineMonitor.o list.o BF.o