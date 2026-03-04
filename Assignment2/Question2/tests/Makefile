# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I../include
# Phony targets to avoid conflicts
.PHONY: all clean 
# Default target: Build the test program
all: test_main
# Rule to link the object file and create the test program executable
test_main: test_main.o ../lib/math_lib.o ../src/utils.o
	$(CC) $(CFLAGS) -o test_main test_main.o ../lib/math_lib.o ../src/utils.o
# Rule to compile test_main.o
test_main.o: test_main.c
	$(CC) $(CFLAGS) -c test_main.c
# Clean target: Remove the object file and the test program executable
clean:
	rm -f test_main.o test_main