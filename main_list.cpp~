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
	//std::cout<<"grafo criado \n";
	//std::string inPath = "old_graphs/as_graph.txt";
	std::string inPath = "../dblp.txt";
	std::string infoPath = "results/graph_info.txt";
	std::string outPath1 = "results/time.txt";
	//std::string outPath2 = "results/graph_DFS.txt";
	Jujuba.loadGraph(inPath, infoPath);
	std::cout<<"grafo carregado \n";
	clock_t time;
	time = clock();
	Jujuba.Diameter();
	time = clock() - time;
	double time_sec;
	time_sec = (double)time;
	time_sec = time_sec/CLOCKS_PER_SEC;
	std::cout<< time << " "<<CLOCKS_PER_SEC <<" " <<time_sec <<endl;
	
	std::cout<<"Fim \n";
	
	std::ofstream outFile;
	outFile.open(outPath1);
	outFile<<std::to_string(time_sec)<<std::endl;
	outFile.close();
	
	

	return 1;
	
}
