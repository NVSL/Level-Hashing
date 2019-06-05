all: plevel

plevel: test.o level_hashing.o hash.o pmdk.o log.o
	gcc -o plevel test.o level_hashing.o hash.o log.o pmdk.o -lm -lpmemobj

pmdk.o: pmdk.c pmdk.h
	gcc -c pmdk.c

hash.o: hash.c hash.h
	gcc -c hash.c
	
level_hashing.o: level_hashing.c level_hashing.h
	gcc -c level_hashing.c

test.o: test.c level_hashing.h
	gcc -c test.c

log.o: log.c log.h
	gcc -c log.c

clean:
	rm -rf *.o plevel
