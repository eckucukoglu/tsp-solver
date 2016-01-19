# *****************************************************
# Parameters to control Makefile operation

CC = g++
CFLAGS = -Wall
DEBUG = -g -DDEBUG

BIN = tsp-solver
# ****************************************************

all: main.o TSP.o
	$(CC) $(CFLAGS) -o $(BIN) main.o TSP.o 

debug: CFLAGS += $(DEBUG)
debug: all

main.o: main.cpp TSP.h
	$(CC) $(CFLAGS) -c main.cpp

TSP.o: TSP.cpp TSP.h
	$(CC) $(CFLAGS) -c TSP.cpp

clean:
	rm -f *.o
	rm -f $(BIN)
