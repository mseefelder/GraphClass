#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graphList.h"
using namespace std;

int main()
{
		cout<<"start \n";
	GraphList Jujuba;
	std::cout<<"grafo criado \n";
	std::string inPath = "old_graphs/ten_graph.txt";
	std::string infoPath = "results/graph_info.txt";
	std::string outPath = "results/graph_BFS.txt";
	Jujuba.loadGraph(inPath, infoPath);
	std::cout<<"grafo carregado \n";
	//Jujuba.BFS(1,outPath);
	//std::cout<<"BFS feita \n";

	return 1;
	
}
