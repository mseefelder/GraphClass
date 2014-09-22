#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <queue>
#include "graph.h"

#include "graphMatrix.h"
using namespace std;

int main()
{
	cout<<"start \n";
	GraphMatrix Grafo;

	std::string inPath = "../subdblp.txt";//substituir pelo caminho desejado
	std::string infoPath = "results/graph_info-matrix.txt";

	Grafo.loadGraph(inPath, infoPath);


	return 1;
	
}
