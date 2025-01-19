CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra

testrunner: store_location.o tests.o
	$(CC) $(CFLAGS) -o testrunner tests.o -lcriterion

store_location.o: src/store_location.c
	$(CC) $(CFLAGS) -c src/store_location.c
	
tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f *.o testrunner