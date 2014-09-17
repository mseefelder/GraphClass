#include "graphMredBool.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>


//using namespace std;


int GraphMatrixRB::loadGraph(std::string path, std::string output){// = OUTPATH){
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
	std::cout<<nVertices<<"\n";
	
	//if (bitMatrix) delete bitMatrix;
	//bitMatrix = new bool[(nVertices*(nVertices-1))/2];

	bitMatrix = new vector<bool> ((nVertices*(nVertices-1))/2, false);

	int vertDegree[nVertices];//for each vertex, store it's degree
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it
	for( int i = 0 ; i<nVertices ; i++) vertDegree[i] = 0;
	
	std::getline(file,line);//gets line here, beacuse last line is eof
	while (!file.eof()){
		std::sscanf(line.c_str(), "%d %d", &x, &y);
		//x;y;// trying not fill the index 0.
		//std::cout<<"Vertices:"<<x<<" "<<y<<"\n";
		x--;y--;
		if(x>y){
			//bitMatrix[((x*x-x)/2)-(x-2)+y-2] = true;}//bruxaria de soma gaussiana, depois explico melhor
			bitMatrix[(((x+1)*x)/2)-x+y] = true;}
		//std::cout<<"ok1 \n";
		else{
			bitMatrix[(((y+1)*y)/2)-y+x] = true;}
		//std::cout<<"ok2 \n";
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
		std::getline(file,line);
	}

	file.close();
	for (int x = 0; x<nVertices;x++){
		degrees[x] = 0;
	}

	for (int j = 0; j<nVertices; j++){
		degrees[vertDegree[j]]+=1;
	}


	std::string degreeString;
	for (int j= 0; j<nVertices; j++){
		degreeString+= std::to_string(j)+" - " +std::to_string(degrees[j]/(float)nVertices)+"\n";
	}	

	d_medio = d_medio/nVertices;

	std::ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;
	outFile.close();
	
	//for(int i = 0; i<nVertices*nVertices; i++){
	//	std::cout<<"i = "<<i<<" - valor na bitMatrix: "<<bitMatrix[i]<<"\n";
	//}

	return 1;
}

int GraphMatrixRB::BFS(int inicial, std::string path){// = "./graphBFS.txt"){
	inicial = inicial -1;

	//std::cout<<"Tamanho da bitmatrix:"<<bitMatrix->size()<<"\n";
	std::queue<int> fifo;
	//bool visited[nVertices]; //we can use vector<bool>
	int parents[nVertices];
	int levels[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			//visited[i]=false;
			parents[i]=-2;
			levels[i]=-1;
	}
	//visited[inicial]=true;
	parents[inicial]=-1;
	levels[inicial]=0;
	fifo.push(inicial);
	
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
			for (int column = 0; column<nVertices; column++){
				if(line>column){
					elementIndex = (((line+1)*line)/2)-(line)+column;}
				else{
					elementIndex = (((column+1)*column)/2)-(column)+line;}
				
					if (bitMatrix[elementIndex]==true){
						//if (!visited[column]){
						if (parents[column]==-2){
							//visited[column]=true;
							fifo.push(column);
							parents[column]=(line);//parece certo
							levels[column]=levels[line]+1;//parece certo
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

	return 1;

}
int GraphMatrixRB::DFS(int inicial, std::string path){
	inicial = inicial -1;
	std::stack<int> lifo;
	int parents[nVertices];
	int levels[nVertices];
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

	return 1;
}
int GraphMatrixRB::connectedComponents(){
	int nComponents = 1 ;
	int edges[nVertices];
	std::queue<int> fifo;
	int line;
	int elementIndex;
	for(int x = 0;x<nVertices;x++){
		edges[x] = 0;
	}
	for(int i = 0;i<nVertices;i++){
		if(edges[i]==0){
			fifo.push(i);
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (int column = 0; column<nVertices; column++){
					if(line>column){
						elementIndex = (((line+1)*line)/2)-(line)+column;}
					else{
						elementIndex = (((column+1)*column)/2)-(column)+line;}
					if (bitMatrix[elementIndex]==true){
						if (edges[column]==0){
							fifo.push(column);
							edges[column] = nComponents;
						}
					}
				}
			fifo.pop();
			}
		nComponents += 1;
		}
	}
	for (int j=0;j<nVertices;j++){
		std::cout<<edges[j]<< "\n";
	}
	return 1;
}

