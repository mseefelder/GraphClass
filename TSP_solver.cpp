#include <iostream>
#include "TSP.h"

int main(int argc, char const *argv[])
{
	std::string open = "../points-1000.txt";
	std::string result = "./result.txt";
	TSP grafo(open);
	grafo.setStartingCity();
	grafo.greedytravel();
	grafo.twoOpt();
	grafo.saveResult(result);
	return 0;
}
