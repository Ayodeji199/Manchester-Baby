# change application name here (executable output name)
TARGET=babymaker

# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`


# linker
# LD=g++
# LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=src/main.c ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp src/errorGui.c ../converter/converter.cpp ../simulator/babySim.cpp

# all: $(OBJS)
# 	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

all: main
    
# main.o: src/main.c ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp ../error/error.cpp ../converter/converter.cpp
# 	$(CC) -c $(CCFLAGS) -o src/main.c ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp ../error/error.cpp ../converter/converter.cpp $(GTKLIB) 
    
main: $(OBJS)
	$(CC) $(CCFLAGS) -rdynamic -g -o ../main.o $(OBJS) $(GTKLIB)

clean:
	rm -f *.o $(TARGET)