# *****************************************************
# Parameters to control Makefile operation

CC = g++
CFLAGS = -Wall
DEBUG = -g -DDEBUG

BIN = tsp-solver
# ****************************************************

all: main.o TSP.o Reader.o
	$(CC) $(CFLAGS) -o $(BIN) main.o TSP.o Reader.o
	strip $(BIN)

debug: CFLAGS += $(DEBUG)
debug: all

main.o: main.cpp TSP.h Reader.h
	$(CC) $(CFLAGS) -c main.cpp

TSP.o: TSP.cpp TSP.h
	$(CC) $(CFLAGS) -c TSP.cpp

Reader.o: Reader.cpp Reader.h
	$(CC) $(CFLAGS) -c Reader.cpp

leakcheck: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(BIN) < test/input > test/output

clean:
	rm -f *.o
	rm -f $(BIN)
	rm -f test/output
