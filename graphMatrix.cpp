#include "graphMatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

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
	
	//std::ifstream file (path , ios::in|ios::binary);
	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::getline (file,line);
	std::sscanf(line.c_str(), "%d", &nVertices);
	
	if (bitMatrix) delete bitMatrix;
	bitMatrix = new bool[(nVertices*(nVertices-1))/2];
	for (int x=0 ;x < (nVertices*(nVertices-1))/2 ; x++){bitMatrix[x] = false;}
	
	int* vertDegree;
	vertDegree = new int[nVertices];//for each vertex, store it's degree
	for( int i = 0 ; i<nVertices ; i++){
		vertDegree[i] = 0;
	}
	
	int* degrees;
	degrees = new int[nVertices-1]; //for each degree, indicate # of vertices that has it
	for (int x = 0; x<nVertices-1;x++){
		degrees[x] = 0;
	}
	
	std::getline(file,line);//gets line here, beacuse last line is eof
	while (!file.eof()){
		std::sscanf(line.c_str(), "%d %d", &x, &y);

		x--;y--;
		
		if(x>y){
			bitMatrix[(((x+1)*x)/2)-x+y] = true;
		}
		
		else{
			bitMatrix[(((y+1)*y)/2)-y+x] = true;
		}
		
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
		std::getline(file,line);
	}
	
	file.close();
	
	int maxDegree = 0;
	for (int j = 0; j<nVertices; j++){
		degrees[vertDegree[j]]+=1;
		if(vertDegree[j]>maxDegree) maxDegree = vertDegree[j];
	}
	
	std::string degreeString;
	float temp = 0.0;
	for (int j= 0; j<maxDegree; j++){
		temp = ((float)degrees[j]/nVertices);
		degreeString+= std::to_string(j)+" - " +std::to_string(temp)+"\n";
	}	
	d_medio = d_medio/nVertices;

	std::ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;
	outFile.close();

	delete [] degrees; delete [] vertDegree;

	return 1;
}

int GraphMatrix::BFS(int inicial, std::string path){// = "./graphBFS.txt"){
	inicial = inicial -1;

	std::queue<int> fifo;
	int* parents;
	parents = new int[nVertices];
	int* levels;
	levels = new int[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			parents[i]=-2;
			levels[i]=-1;
	}
	parents[inicial]=-1;
	levels[inicial]=0;
	fifo.push(inicial);
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			line = fifo.front();
			for (int column = 0; column<nVertices; column++){
				if (line!=column){
				if(line>column){
					elementIndex = (((line+1)*line)/2)-(line)+column;}
				else{
					elementIndex = (((column+1)*column)/2)-(column)+line;}
				
					if (bitMatrix[elementIndex]==true){
						if (parents[column]==-2){
							fifo.push(column);
							parents[column]=line;
							levels[column]=levels[line]+1;
						}
					}
				}
			}	
			fifo.pop();
	}
	
	std::string vertexString;
	for (int j= 0; j<nVertices; j++){
		vertexString+= "V: "+std::to_string(j+1)+" Pai: "+std::to_string(parents[j]+1)+" Nivel: "+std::to_string(levels[j])+"\n";
	}	
	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da BFS: \n"<<vertexString<<std::endl;
	outFile.close();
	delete [] parents; delete [] levels;

	return 1;

}
int GraphMatrix::DFS(int inicial, std::string path){
	inicial = inicial -1;
	std::stack<int> lifo;
	int* parents;
	parents = new int[nVertices];
	int* levels;
	levels = new int[nVertices];
	for (int i = 0; i<nVertices;i++){
		parents[i] = -2;
		levels[i] = -1;
	}
	parents[inicial] = -1;
	levels[inicial] = 0;
	lifo.push(inicial);

	int line = 0;
	int elementIndex = 0;
	while(!lifo.empty()){
		line = lifo.top();
		lifo.pop();
		for (int column = 0; column<nVertices;column++){
			if (line>column){
				elementIndex = (((line+1)*line)/2)-(line)+column;}
			else {
				elementIndex = (((column+1)*column)/2)-(column)+line;}
			if (bitMatrix[elementIndex] == true){
				if (parents[column]==-2){
					lifo.push(column);
					parents[column] = line;
					levels[column] = levels[line] +1;
				}
			}
		}
	}
	std::string vertexString;
	for (int j= 0; j<nVertices; j++){
		vertexString+= "V: "+std::to_string(j+1)+" Pai: "+std::to_string(parents[j]+1)+" Nivel: "+std::to_string(levels[j])+"\n";
	}	

	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da DFS: \n"<<vertexString<<std::endl;
	outFile.close();

	delete [] parents; delete [] levels;

	return 1;
}

int GraphMatrix::connectedComponents(){
	int nComponents = 0;
	std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >,CompareDist > myHeap;
	bool* vertices;
	vertices = new bool[nVertices];
	std::queue<int> fifo;
	int line;
	int size = 0;
	int elementIndex;
	for(int x = 0;x<nVertices;x++){
		vertices[x] = false;
	}
	std::cout << "comeca primeira bfs !\n";
	for(int i = 0;i<nVertices;i++){
		size = 0;
		if(vertices[i]==false){
			fifo.push(i);
			vertices[i] = true;
			size++;
			nComponents++;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (int column = 0; column<nVertices; column++){
					if (column!=line){
					if(line>column){
						elementIndex = (((line+1)*line)/2)-(line)+column;}
					else{
						elementIndex = (((column+1)*column)/2)-(column)+line;}
					if (bitMatrix[elementIndex]==true){
						if (vertices[column]==false){
							fifo.push(column);
							vertices[column] =true;
							size++;
						}
					}
				}
			}
			fifo.pop();
			}
		myHeap.emplace(i,size);
		}
	}
	//FIM DA FIRST BFS
	std::cout << "termina primeira bfs !\n";
	std::cout << nComponents << std::endl;
	int counter = 0;
	int vertice = 0;
	int** ccOrder;
	ccOrder =  new int*[nComponents];
	//SECOND BFS
	std::cout << "comeca segunda bfs !\n";
	for (int i = 0;i<nComponents;i++){
		counter = 2;
		size = myHeap.top().second;
		ccOrder[i] = new int[size+1];
		vertice = myHeap.top().first;
		ccOrder[i][0] = size;
		ccOrder[i][1] = vertice +1;
		myHeap.pop();
		fifo.push(vertice);
		vertices[vertice] = false;
		while(!fifo.empty()){
			line = fifo.front();
			for (int column = 0; column<nVertices;column++){
				if(column!=line){
				if(line>column){
					elementIndex = (((line+1)*line)/2)-(line)+column;}
				else{
					elementIndex = (((column+1)*column)/2)-(column)+line;}
				if(bitMatrix[elementIndex]==true){
					if (vertices[column]==true){
						fifo.push(column);
						vertices[column] = false;
						ccOrder[i][counter] = column+1;
						counter++;

					}
				}
			}
		}
		fifo.pop();
		}
	}
	//FIM DA SECOND BFS
	std::cout << "termina second bfs !\n";
	std:: string path = "results/connectedComp-matrix.txt";
	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Componentes conexas: \n";
	for ( int j = 0;j<nComponents;j++){
		size = ccOrder[j][0];
		outFile<<"Componente #"<<j<<" - Tamanho: "<<size<<"\n";
		for (int i = 1; i <size+1; i++){
			outFile<<ccOrder[j][i]<<", ";
		}
		outFile<<"\n";
		delete [] ccOrder[j];
	}
	outFile<<std::endl;
	outFile.close();
	delete [] vertices; delete [] ccOrder;

	return 1;
}

int GraphMatrix::Diameter(){
	
	std::cout<<"NOT IMPLEMENTED"<<std::endl;	
	
	return 0;

}

