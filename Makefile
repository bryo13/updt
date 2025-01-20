CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra

testrunner: store_location.o db.o db.o tests.o
	$(CC) $(CFLAGS) -o testrunner tests.o -lcriterion -lsqlite3

store_location.o: src/store_location.h
	$(CC) $(CFLAGS) -c src/store_location.h
	
db.o: src/db.c
	$(CC) $(CFLAGS) -c src/db.c

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f *.o testrunner