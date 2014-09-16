#include "graphMatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>


//using namespace std;


int GraphMatrix::loadGraph(std::string path, std::string output){// = OUTPATH){
	std::string line;
	int x,y, mEdges;
	float d_medio;
	
	nVertices= 0;
	x = 0;
	y = 0;
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;
	if (bitMatrix) delete bitMatrix;
	bitMatrix = new std::vector<bool>;
	//std::ifstream file (path , ios::in|ios::binary);
	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::getline (file,line);
	std::sscanf(line.c_str(), "%d", &nVertices);
	std::cout<<nVertices<<"\n";

	bitMatrix->resize(nVertices*nVertices,false); //resizing the bitMatrix to a fix size
	int vertDegree[nVertices];//for each vertex, store it's degree
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it
	for( int i = 0 ; i<nVertices ; i++) vertDegree[i] = 0;
	
	std::getline(file,line);
	while (!file.eof()){
		//std::getline(file,line);
		std::sscanf(line.c_str(), "%d %d", &x, &y);
		x--;y--;// trying not fill the index 0.
		std::cout<<"Vertices:"<<x<<" "<<y<<"\n";
		bitMatrix->assign(x*nVertices+y, true);
		std::cout<<"ok1 \n";
		bitMatrix->assign(y*nVertices+x, true);// redundance
		std::cout<<"ok2 \n";
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
		std::getline(file,line);
	}

	file.close();

	for (int j = 0; j<nVertices; j++){
		degrees[vertDegree[j]]++;
	}


	std::string degreeString;
	for (int j= 0; j<nVertices; j++){
		degreeString+= std::to_string(j)+" -  " +std::to_string(degrees[j]/(float)nVertices)+" aqui acaba uma linha\n";
	}	

	d_medio = d_medio/nVertices;

	std::ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;
	outFile.close();
	
	for(int i = 0; i<nVertices*nVertices; i++){
		std::cout<<"i = "<<i<<" - valor na bitMatrix: "<<bitMatrix[i]<<"\n";
	}

	return 1;
}

int GraphMatrix::BFS(int inicial, std::string path){// = "./graphBFS.txt"){
	inicial = inicial -1;

	std::cout<<"Tamanho da bitmatrix:"<<bitMatrix->size()<<"\n";
	std::queue<int> fifo;
	bool visited[nVertices]; //we can use vector<bool>
	int parents[nVertices];
	int levels[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			visited[i]=false;
			parents[i]=-2;
			levels[i]=-1;
	}
	visited[inicial]=true;
	parents[inicial]=-1;
	levels[inicial]=0;
	fifo.push(inicial);
	
	int line = 0;
	int elementIndex=0;
	while(fifo.size()!=0){
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
			for (int column = 0; column<nVertices; column++){
				elementIndex = line*nVertices+column;
				std::cout<<elementIndex<<"\n";
					if (bitMatrix->at(elementIndex)==true){
						visited[column]=true;
						fifo.push(column);
						parents[column]=line;
						levels[column]=levels[line]+1;
					}
			}

	}
	std::string vertexString;
	for (int j= 0; j<nVertices; j++){
		vertexString+= "V: "+std::to_string(j+1)+"Pai: "+std::to_string(parents[j]+1)+"Nivel: "+std::to_string(levels[j])+"\n";
	}	

	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da BFS: \n"<<vertexString<<std::endl;
	outFile.close();

	return 1;

}


