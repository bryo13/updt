CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra -MMD

test: source_location.o db.o watch_args.o tests.o
	$(CC) $(CFLAGS) -o test tests.o -lcriterion -lsqlite3

build: main.o db.o source_location.o watch_args.o dest_location.o
	$(CC) $(CFLAGS) -o updt main.o -lsqlite3

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

db.o: src/db.c include/db.h
	$(CC) $(CFLAGS) -c src/db.c

source_location.o: src/source_location.c include/source_location.h
	$(CC) $(CFLAGS) -c src/source_location.c
	
watch_args.o: src/watch_args.c
	$(CC) $(CFLAGS) -c src/watch_args.c

dest_location.o: src/dest_location.c include/dest_location.h
	$(CC) $(CFLAGS) -c src/dest_location.c 

tests.o: tests/tests.c
	$(CC) $(CFLAGS) -c tests/tests.c

clean:
	rm -f -r *.o *.d test updt /home/brian/.updt
