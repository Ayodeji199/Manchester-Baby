# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic -Werror
CFLAGS_LESSER = -Wall -Werror
CVERSION = -std=c++17

# Main
all: realMaxTester

realMaxTester: testers/realMaxTester.cpp assembler/assembler.cpp
	# Compiles program
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o realMaxTester.o testers/realMaxTester.cpp assembler/assembler.cpp

clean :
	# Deletes unused files
	-rm $(objects) *.o