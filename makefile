
IDIR=./include
CFLAGS=-I$(IDIR)
CC = g++
TOOLS_FOLDER = ./tools
BIN = ./bin

ODIR=bin
LIBS=-lm

./bin/%.o: ./src/%.C
	$(CC) -c $< -o $@ $(CFLAGS)

main: ./bin/main.o  ./bin/HT.o ./bin/decoder.o ./bin/parseMessage.o
	$(CC) -o $@ $^ $(CFLAGS) 

bin/main.o: src/main.C include/decoder.h

bin/HT.o: src/HT.C include/HT.h

bin/decoder.o: ./src/decoder.C

./bin/parseMessage.o: ./src/parseMessage.C ./include/parseMessage.h ./include/can.h ./include/HT.h

# RUNS THE MAIN FILE
run: main
	./main

# CLEANS ALL FILES IN DIRECTORY
clean: 
	rm -f ./bin/*.o main