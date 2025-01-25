# This is an example makefile. You may use this as a model for your own, to be used in the challenge


CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

# Final executable name
TARGET = test

# Object files
OBJS = history_list.o simple_history.o

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation rules
history_list.o: history_list.c history_list.h
	$(CC) $(CFLAGS) -c history_list.c

simple_history.o: simple_history.c
	$(CC) $(CFLAGS) -c simple_history.c

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean