# Sets default compiler
# CC = g++

# Sets flags
# CFLAGS = -Wall -Wextra -pedantic -Werror
# CFLAGS_LESSER = -Wall -Werror
# CVERSION = -std=c++17

# Compiles assembler
g++ -std=c++17 -o assembler.o assembler/assembler.cpp

# Compiles simulator
g++ -std=c++17 -o simulator.o simulator/main.cpp