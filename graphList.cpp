#include "graphList.h"

int GraphList::loadGraph(std::string path,std::string output){// = "./graphInfo.txt"){
	std::string line;
	int nVertices,x,y,mEdges;
	float d_medio; //(sum of all degrees)/number of vertices()
	
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;
	
	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::getline (file,line);
	std::sscanf(line.c_str(), "%d", &nVertices);
	
	graph = new linkedList[nVertices];
	int vertDegree[nVertices];//for each vertex, store it's degree
	for (int i = 0; i<nVertices; i++){
			vertDegree[i]=0;
	}
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it
	
	for (int i = 0; i<(nVertices-1); i++){
			degrees[i]=0;
	}
	
	std::getline(file,line);
	while (!file.eof()){
		//getline(file,line);
		std::sscanf(line.c_str(), "%d %d", &x, &y);
		x--; y--;
		std::cout<<"Verts: "<<x<<" - "<<y<<"\n";
		graph[x].insert(y);
		graph[y].insert(x);
		std::cout<<"Foi! \n";
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		std::cout<<"Degrees foi! \n";
		d_medio+=2.0;
		std::getline(file,line);
	}

	file.close();
	std::cout<<"Arquivo lido! \n";
	for (int j = 0; j<nVertices; j++){
		std::cout<<"Vert: "<<j+1<<" Degree: "<<vertDegree[j]<<":";
		degrees[vertDegree[j]]++;
		std::cout<<"Works! \n";
	}

	std::cout<<"Degrees salvo \n";

	std::string degreeString;
	for (int j= 0; j<nVertices; j++){
		degreeString+=std::to_string(j)+std::to_string(degrees[j]/(float)nVertices)+"\n";
	}	

	std::cout<<"Degreestring salvo! \n";

	d_medio = d_medio/nVertices;

	std::ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;

	return 1;

}
