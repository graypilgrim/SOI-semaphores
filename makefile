CC=gcc
CFLAGS=-Wall -Werror -pedantic -O2
OBJS=producers.o consumer.o main.o tools.o

sem: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm sem

.PHONY: clean
