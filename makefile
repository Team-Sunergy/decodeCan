
# this makefile heavily inspired by
# https://stackoverflow.com/questions/26028834/makefile-move-object-files

CFLAGS = -g -O3
CC = g++

# PATHS FOR .c .h .o
TOOLS_PATH = ./tools/
BIN_PATH = ./bin/
INC_PATH = ./include/

TARGET = main

# files to compile 
OBJ1 = 	HT.o \

MAINF = main.o

# appends Bin path to beginning of OBJ
#OBJ = $(patsubst %, $(BIN_PATH)%, $(OBJ1))

# # Build o files for current directory
# $(BIN_PATH)%.o: %.C
# 			@echo [CC] $<
# 			@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)


# Build o files for tools
$(BIN_PATH)%.o: $(TOOLS_PATH)%.C $(INC_PATH)%.h
			@echo [CC] compiling: $@ $<
			@$(CC) $(CFLAGS) -o $@ -c $< 

$(TARGET):	($(BIN_PATH)$(OBJ)) $(BIN_PATH)$(MAINF)
			@echo [ALERT] creating executable $(TARGET) [ALERT]
			@echo [ALERT] using: $^ [ALERT]
			@$(CC) -o $@ $^ 

# compiles main.C and puts .o in the bin
$(BIN_PATH)$(MAINF): main.C
	$(CC) $(CFLAGS) -c main.C -o $(BIN_PATH)$(MAINF)


# RUNS THE MAIN FILE
run: $(TARGET)
	./main.exe

# CLEANS ALL FILES IN DIRECTORY
clean: 
	rm -f *.exe *.o
	rm -f bin/*.o