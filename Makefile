CC 		  = cc
CFLAGS  = -Wall
OUTNAME = ht

ht: main.o htable.o
	$(CC) $(CFLAGS) -o $(OUTNAME) main.o htable.o -lncurses

main.o: main.c htable.h
	$(CC) -c main.c

htable: htable.c htable.h
	$(CC) -c htable.c
