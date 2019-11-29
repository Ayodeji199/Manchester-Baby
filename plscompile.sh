# Sets default compiler
CC=g++

# Sets flags
CFLAGS="-Wall -Wextra -pedantic -Werror"
CFLAGS_LESSER="-Wall -Werror"
CVERSION="-std=c++17"

# Compiles assembler
$CC $CVERSION $CFLAGS_LESSER -o assembler.o assembler/main.cpp assembler/assembler.cpp assembler/opcodes.cpp assembler/symbols.cpp file/file.cpp error/error.cpp converter/converter.cpp

# Compiles simulator
$CC $CVERSION $CFLAGS_LESSER -o simulator.o simulator/main.cpp simulator/babySim.cpp file/file.cpp error/error.cpp converter/converter.cpp