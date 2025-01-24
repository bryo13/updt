CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra 

test: store_location.o db.o args.o tests.o
	$(CC) $(CFLAGS) -o test tests.o -lcriterion -lsqlite3

build: main.o
	$(CC) $(CFLAGS) -o updt main.o -lsqlite3

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

store_location.o: src/includes/store_location.h
	$(CC) $(CFLAGS) -c src/includes/store_location.h
	
args.o: src/args.c
	$(CC) $(CFLAGS) -c src/args.c

db.o: src/db.c
	$(CC) $(CFLAGS) -c src/db.c

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f -r *.o test updt /home/brian/.updt