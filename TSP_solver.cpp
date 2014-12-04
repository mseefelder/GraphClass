#include <iostream>
#include "graph.h"

int main(int argc, char const *argv[])
{
	GraphTSP<adjMatrix> grafo(open);
	grafo.setStartingPoint();
	grafo.solveRandom();
	grafo.two_opt();


	return 0;
}