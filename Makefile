CC      = gcc
CFLAGS = -Wall -pedantic
OBJECTS = 537ps.o processIDS.o process.o

537ps: $(OBJECTS)
	$(CC) $(CFLAGS) -o 537ps $(OBJECTS)

537ps.o: 537ps.c processIDS.h process.h
	$(CC) $(CFLAGS) -c 537ps.c

processIDS.o: processIDS.c processIDS.h
	$(CC) $(CFLAGS) -c processIDS.c

process.o: process.c process.h processIDS.h
	$(CC) $(CFLAGS) -c process.c

clean:
	rm -f $(OBJECTS) 537ps
