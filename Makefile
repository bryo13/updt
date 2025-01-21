CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra

testrunner: store_location.o db.o db.o args.o tests.o
	$(CC) $(CFLAGS) -o testrunner tests.o -lcriterion -lsqlite3

store_location.o: src/includes/store_location.h
	$(CC) $(CFLAGS) -c src/includes/store_location.h
	
args.o: src/args.c
	$(CC) $(CFLAGS) -c src/args.c

db.o: src/db.c
	$(CC) $(CFLAGS) -c src/db.c

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f -r *.o testrunner /home/brian/.updt