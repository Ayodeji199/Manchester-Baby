# BabyMaker
BabyMaker - A Simulation of the Manchester Baby Computer also called the Small-Scale Experimental Machine (SSEM) from 1948

Relax it's only just 1s and 0s.

Run make to compile everything, there may be a need for gtk libraries in order to compile the gui. If these are not present, run make assembler simulator instead.
There's a also an alternative bash script plscompile.sh because the makefile is incredibly temperamental. 
To run each program use ./assembler.o, ./simulator.o.
The simulator must be used with a -readname file argument to specify the input file.  