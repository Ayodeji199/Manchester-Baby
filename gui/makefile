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
LD=g++
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=main.o

# all: $(OBJS)
# 	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

all: main
    
# main.o: src/main.cpp ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp ../error/error.cpp ../converter/converter.cpp
# 	$(CC) -c $(CCFLAGS) -o src/main.cpp ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp ../error/error.cpp ../converter/converter.cpp $(GTKLIB) 
    
main: 
	$(CC) $(CCFLAGS) -o main.o src/main.cpp ../assembler/assembler.cpp ../assembler/opcodes.cpp ../assembler/symbols.cpp ../file/file.cpp ../error/error.cpp ../converter/converter.cpp $(GTKLIB) -rdynamic

clean:
	rm -f *.o $(TARGET)