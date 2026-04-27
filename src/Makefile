CC = gcc
CFLAGS = -Wall -g

gndcontrol: gndcontrol.o airs_protocol.o airplane.o util.o
	$(CC) $(CFLAGS) -o gndcontrol gndcontrol.o airs_protocol.o airplane.o util.o

%.o: %.c
	$(CC) $(CFLAGS) -c $

clean:
	rm -f *.o gndcontrol

