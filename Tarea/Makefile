CCFLAGS = -g -Wall

pscheduler: main.c queues.o 
	gcc $(CCFLAGS) main.c queues.o  -o $@


queues.o: queues.h queues.c
	gcc -g -c  queues.c -o queues.o


clean:
	rm -rf *.o pscheduler
