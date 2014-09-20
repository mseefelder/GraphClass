#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graphListS.h"
#include <omp.h>
using namespace std;

int main()
{
	cout<<"start \n";
	GraphListS Jujuba;
	std::cout<<"grafo criado \n";
	//std::string inPath = "old_graphs/ten_graph.txt";
	std::string inPath = "as_graph.txt";
	std::string infoPath = "results/graph_info.txt";
	std::string outPath1 = "results/graph_BFS.txt";
	std::string outPath2 = "results/graph_DFS.txt";
	Jujuba.loadGraph(inPath, infoPath);
	std::cout<<"grafo carregado \n";
	clock_t time;
	time = clock();
	for (int i = 1;i<11;i++){
	Jujuba.DFS(i,outPath2);
	std::cout<<"DFS feita \n";
	}
	time = clock() - time;
	double time_sec;
	time_sec = (double)time;
	time_sec = time_sec/CLOCKS_PER_SEC;
	std::cout<< time << " "<<CLOCKS_PER_SEC <<" " <<time_sec <<endl;
	
	Jujuba.DFS(4,outPath2);
	std::cout<<"DFS feita \n";
	Jujuba.connectedComponents();
	std::cout<<"Fim \n";

	return 1;
	
}
