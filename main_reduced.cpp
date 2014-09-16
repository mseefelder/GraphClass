#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <queue>
#include "graph.h"

#include "graphMred.h"
using namespace std;

int main()
{
	/*string line;
	int n,x,y;
	char * value = NULL;
	vector<bool> bitMatrix;
	//bool** graphMatrix;
	ifstream file ("as_graph.txt",ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &n);
	if (true){
		//graphMatrix= new bool*[n-1];
		bitMatrix.resize(n*n, false);
		for ( int i = 0; i< n-1; i++){
			//graphMatrix[i] = new bool [n-1];
			for( int j = 0 ; j < n-1 ; j++){
				//graphMatrix[i][j] = false;
				cout<<bitMatrix[1*n+1]<<endl;
			}
		}	
		while (!file.eof()){
			getline(file,line);
			//if (value) delete value;
			//value = strtok(line.c_str()," ");
			//x = atoi(value);
			//delete value;
			//value = strtok(line.c_str()," ");
			//y = atoi(value);
			sscanf(line.c_str(), "%d %d", &x, &y);
			//graphMatrix[y][x] = true;
			x--;
			y--;
			bitMatrix[x*n+y] = true;
			bitMatrix[y*n+x] = true;
			//graphMatrix[y][x] = true;
		}
	}
	
	cout<<bitMatrix[9*n+249]<<endl;*/

	/*
	string line;
	int nVertices,x,y, mEdges;
	float d_medio;

	nVertices= 0;
	x = 0;
	y = 0;
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;
	vector<bool> bitMatrix;
	ifstream file ("as_graph.txt" , ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &nVertices);

	bitMatrix.resize(nVertices*nVertices,false); //resizing the bitMatrix to a fix size
	int vertDegree[nVertices];//for each vertex, store it's degree
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it
	for( int i = 0 ; i<nVertices ; i++) vertDegree[i] = 0;

	while (!file.eof()){
		getline(file,line);
		sscanf(line.c_str(), "%d %d", &x, &y);
		x--;y--;// trying not fill the index 0.
		bitMatrix[x*nVertices+y] = true;
		bitMatrix[y*nVertices+x] = true;// redundance
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
	}

	file.close();

	for (int j = 0; j<nVertices; j++){
		degrees[vertDegree[j]]++;
	}


	string degreeString;
	for (int w= 0; w<nVertices; w++){
		degreeString+= std::to_string(w)+ " " + std::to_string(degrees[w]/(float)nVertices)+"\n";
	}
	d_medio = d_medio/nVertices;

	ofstream outFile;
	outFile.open("./graphInfo.txt");
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<endl;
	outFile.close();
	*/
	cout<<"start \n";
	GraphMatrixR Jujuba;
	std::cout<<"grafo criado \n";
	std::string inPath = "old_graphs/as_graph.txt";
	std::string infoPath = "results/graph_info.txt";
	std::string outPath = "results/graph_BFS.txt";
	Jujuba.loadGraph(inPath, infoPath);
	std::cout<<"grafo carregado \n";
	Jujuba.BFS(1,outPath);
	std::cout<<"BFS feita \n";

	return 1;
	
}
