# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I../include
# Phony targets to avoid conflicts
.PHONY: all clean
# Default target: Build the main program
all: main
# Rule to link the object files and create the program executable
main: main.o utils.o ../lib/math_lib.o
	$(CC) $(CFLAGS) -o main main.o utils.o ../lib/math_lib.o
# Rules to compile main.o and utils.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c
# Clean target: Remove the object files and the program executable
clean:
	rm -f main.o utils.o main