CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra

testrunner: store_location.o db.o db.o read_args.o tests.o
	$(CC) $(CFLAGS) -o testrunner tests.o -lcriterion -lsqlite3

store_location.o: src/includes/store_location.h
	$(CC) $(CFLAGS) -c src/includes/store_location.h
	
read_args.o: src/read_args.c
	$(CC) $(CFLAGS) -c src/read_args.c

db.o: src/db.c
	$(CC) $(CFLAGS) -c src/db.c

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f *.o testrunner