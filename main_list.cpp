#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graphList.h"
#include <omp.h>
#include <unistd.h>
using namespace std;

int main()
{
	int incr = -20;
	int ret;
	
	ret = nice(incr);	
	
	cout<<ret<<" start \n";
	GraphList Grafo;

	std::string inPath = "../as_graph.txt";//substituir pelo caminho desejado
	std::string infoPath = "results/graph_info.txt";
	std::string bfsPath = "results/graph_bfs.txt";
	
	Grafo.loadGraph(inPath, infoPath);
	int n = Grafo.getNumberOfVertices();
	
	clock_t time;
	time = clock();
	Grafo.BFS(1,bfsPath);
	time = clock() - time;
	double time_sec;
	time_sec = (double)time;
	time_sec = time_sec/CLOCKS_PER_SEC;
	std::cout<< time << " "<<CLOCKS_PER_SEC <<" " <<time_sec <<endl;	

	return 1;
	
}
