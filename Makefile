CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra 

test: source_location.o db.o watch_args.o tests.o
	$(CC) $(CFLAGS) -o test tests.o -lcriterion -lsqlite3

build: main.o
	$(CC) $(CFLAGS) -o updt main.o -lsqlite3

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

source_location.o: src/includes/source_location.h
	$(CC) $(CFLAGS) -c src/includes/source_location.h
	
watch_args.o: src/watch_args.c
	$(CC) $(CFLAGS) -c src/watch_args.c

db.o: src/includes/db.h
	$(CC) $(CFLAGS) -c src/includes/db.h

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f -r *.o test updt /home/brian/.updt
