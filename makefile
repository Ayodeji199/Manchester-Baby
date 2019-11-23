# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic -Werror
CFLAGS_LESSER = -Wall -Werror
CVERSION = -std=c++17

# Main
all: realMaxTester

realMaxTester: tester/realMaxTester.cpp assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp file/file.cpp error/error.cpp
	# Compiles real max tester
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o realMaxTester.o assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp tester/realMaxTester.cpp file/file.cpp error/error.cpp

assembler: assembler/assembler.cpp file.file.cpp error/error.cpp
	# Compiles assembler
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o assembler.o assembler/assembler.cpp file/file.cpp error/error.cpp

clean :
	# Deletes unused files
	-rm $(objects) *.o