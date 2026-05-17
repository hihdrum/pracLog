CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -MMD

%o : %c
	$(CC) $(CFLAGS)

main : main.o log_time.o log_generator.o \
       f001data.o f002data.o f003data.o randInt.o
	$(CC) $(CFLAGS) $^ -o main

tags : *.c *.h
	ctags *.[ch]

-include *d

clean:
	rm -f *.o *.d a.out tags main
