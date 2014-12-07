#include <iostream>
#include "TSP.h"
#include "graph.h"

int main(int argc, char const *argv[])
{
	std::string open = "../points-10.txt";
	std::string pre = "./pre2.txt";
	std::string pos = "pos2.txt";
	TSP grafo(open);
	grafo.setStartingCity();
	grafo.solveLinear();
	grafo.saveResult(pre);
	grafo.twoOpt();
	grafo.saveResult(pos);


	return 0;
}
