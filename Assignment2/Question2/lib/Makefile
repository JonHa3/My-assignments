# Variables
CC = gcc
CFLAGS = -Wall -Wextra

# Phony targets to avoid conflicts
.PHONY: all clean
# Default target: Build the object file for the math library
all: math_lib.o

# Rule to build math_lib.o from math_lib.c
math_lib.o: math_lib.c
	@echo "Building object file for math library"
	$(CC) $(CFLAGS) -c math_lib.c

# Clean target: Remove the object file
clean:
	rm -f math_lib.o