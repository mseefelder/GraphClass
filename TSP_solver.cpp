#include <iostream>
#include "TSP.h"

int main(int argc, char const *argv[])
{
	std::string open = "../points-5000.txt";
	std::string pre = "./pre2.txt";
	std::string pos = "pos2.txt";
	TSP grafo(open);
	std::cout<<"Opened."<<std::endl;
	grafo.setStartingCity();
	std::cout<<"Starting city set."<<std::endl;
	grafo.greedytravel();
	std::cout<<"Problem solved."<<std::endl;
	grafo.saveResult(pre);
	std::cout<<"Result saved."<<std::endl;
	grafo.twoOpt();
	std::cout<<"2-OPT finished."<<std::endl;
	grafo.saveResult(pos);
	std::cout<<"Result saved [2]."<<std::endl;
	return 0;
}
