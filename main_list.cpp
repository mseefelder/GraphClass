#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graphList.h"
#include <omp.h>
using namespace std;

int main()
{
	cout<<"start \n";
	GraphList Grafo;

	std::string inPath = "../subdblp.txt";//substituir pelo caminho desejado
	std::string infoPath = "results/graph_info.txt";

	Grafo.loadGraph(inPath, infoPath);

	return 1;
	
}
