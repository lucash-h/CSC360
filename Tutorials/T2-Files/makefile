# This is an example makefile. You may use this as a model for your own, to be used in the challenge


CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

# Final executable name
TARGET = test

# Object files
OBJS = main.o add.o

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation rules
main.o: main.c add.h
	$(CC) $(CFLAGS) -c main.c

add.o: add.c add.h
	$(CC) $(CFLAGS) -c add.c

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean