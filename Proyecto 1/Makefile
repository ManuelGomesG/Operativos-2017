CCFLAGS = -g -Wall -std=gnu99

els: main.c listing.o
	gcc $(CCFLAGS) main.c listing.o  -o $@


listing.o: listing.h listing.c
	gcc -g -c  listing.c -o listing.o


clean:
	rm -rf *.o els
