GraphClass
==========

Class to work with graphs.

To use it, include "graph.h" on your project.

Attention, requires OpenMP (omp.h). Compile with -fopenmp flag.
Attention, requires std version = c++11. Compile with -std=c++11 flag.

To compile the main.cpp example:

g++ -std=c++11 -fopenmp -o output adjlist.cpp adjmatrix.cpp graph.cpp main.cpp
