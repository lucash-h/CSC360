CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = history_list.o simple_history.o

simple_history: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

history_list.o: history_list.c history_list.h
	$(CC) $(CFLAGS) -c history_list.c

simple_history.o: simple_history.c history_list.h
	$(CC) $(CFLAGS) -c simple_history.c

clean:
	rm -f simple_history $(OBJS)