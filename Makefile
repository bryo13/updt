CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra

testrunner: homedir.o tests.o
	$(CC) $(CFLAGS) -o testrunner tests.o -lcriterion

homedir.o: src/homedir.c
	$(CC) $(CFLAGS) -c src/homedir.c

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f *.o testrunner