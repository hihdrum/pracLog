CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -MMD

%o : %c
	$(CC) $(CFLAGS)

main : main.o log.o log_time.o f001data.o randInt.o
	$(CC) $(CFLAGS) $^ -o main

tags :
	ctags *.[ch]

-include *d

clean:
	rm -f *.o *.d a.out tags main
