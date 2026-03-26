CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -MMD

%o : %c
	$(CC) $(CFLAGS)

main : main.o log_time.o
	$(CC) $(CFLAGS) main.o log_time.o -o main

-include *d

clean:
	rm -f *.o *.d a.out tags main
