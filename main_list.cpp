#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graphListS.h"
using namespace std;

int main()
{
		cout<<"start \n";
	GraphListS Jujuba;
	std::cout<<"grafo criado \n";
	std::string inPath = "old_graphs/ten_graph.txt";
	//std::string inPath = "../dblp.txt";
	std::string infoPath = "results/graph_info.txt";
	std::string outPath1 = "results/graph_BFS.txt";
	std::string outPath2 = "results/graph_DFS.txt";
	Jujuba.loadGraph(inPath, infoPath);
	std::cout<<"grafo carregado \n";
	Jujuba.BFS(1,outPath1);
	std::cout<<"BFS feita \n";
	Jujuba.DFS(1,outPath2);
	std::cout<<"DFS feita \n";
	Jujuba.connectedComponents();
	std::cout<<"Fim \n";

	return 1;
	
}