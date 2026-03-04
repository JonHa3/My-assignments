# Variables
CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = program

ifeq ($(BUILD), debug)
	CFLAGS += -g -DDEBUG
endif

debug:
	$(MAKE) BUILD=debug all
# Phony targets
.PHONY: all clean debug tests

# Default target
all: $(TARGET)

# Rule to build program
$(TARGET): main.o math_utils.o io_utils.o
	$(CC) $^ -o $@
# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# Clean target
clean:
	rm -f *.o $(TARGET)
# Run target (Optional)
tests: 
	$(MAKE) -C tests/