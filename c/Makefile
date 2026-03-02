CFLAGS += -Wall
CFLAGS += -g
CFLAGS += -MMD

%o : %c
	$(CC) $(CFLAGS)

main : main.o
	$(CC) $(CFLAGS) main.o -o main

-include *d

clean:
	rm -f *.o *.d a.out tags main
