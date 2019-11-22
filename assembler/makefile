# Sets default compiler
CC = g++

# Sets flags
CFLAGS = -Wall -Wextra -pedantic -Werror
CFLAGS_LESSER = -Wall -Werror
CVERSION = -std=c++17

# Main
all: assembler

assembler: assembler.cpp opcodes.cpp symbols.cpp ../file/file.cpp ../converter/converter.cpp
	# Compiles assembler
	$(CC) $(CVERSION) $(CFLAGS_LESSER) -o assembler assembler.cpp opcodes.cpp symbols.cpp ../file/file.cpp ../converter/converter.cpp

clean :
	# Deletes unused files
	-rm $(objects) *.o