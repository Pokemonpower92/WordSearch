CC=g++
CFLAGS=-std=c++11
INCLUDE=include
BIN = bin/MakeSearch 

all: $(BIN)

clean: 
	rm -f bin/* obj/*

obj/WordSearch.o: src/WordSearch.cpp include/WordSearch.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o obj/WordSearch.o src/WordSearch.cpp

obj/MakeSearch.o: src/MakeSearch.cpp include/WordSearch.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o obj/MakeSearch.o src/MakeSearch.cpp

bin/MakeSearch: obj/MakeSearch.o obj/WordSearch.o
	$(CC) $(CFLAGS) -I$(INCLUDE) -o bin/MakeSearch obj/MakeSearch.o obj/WordSearch.o

