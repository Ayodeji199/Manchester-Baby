# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic -Werror -Wno-write-strings
CFLAGS_LESSER = -Wall -Werror -Wno-write-strings
CVERSION = -std=c++17

# Main
all: assembler, simulator 

realMaxTester: tester/realMaxTester.cpp assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp converter/converter.cpp file/file.cpp error/error.cpp
	# Compiles real max tester
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o realMaxTester.o tester/realMaxTester.cpp assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp converter/converter.cpp file/file.cpp error/error.cpp 

assembler: assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp file/file.cpp error/error.cpp converter/converter.cpp
	# Compiles assembler
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o assembler.o assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp file/file.cpp error/error.cpp converter/converter.cpp

simulator: simulator/main.cpp simulator/babySim.cpp file/file.cpp error/error.cpp converter/converter.cpp
	# Compiles simulator
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o simulator.o simulator/main.cpp simulator/babySim.cpp file/file.cpp error/error.cpp converter/converter.cpp

clean :
	# Deletes unused files
	-rm $(objects) *.o
