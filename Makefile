all: vaccineMonitor

vaccineMonitor: vaccineMonitor.o list.o
	gcc vaccineMonitor.o list.o -o vaccineMonitor

vaccineMonitor.o: vaccineMonitor.c
	gcc -c vaccineMonitor.c

list.o: list.c
	gcc -c list.c

clean:
	rm -f vaccineMonitor vaccineMonitor.o list.o