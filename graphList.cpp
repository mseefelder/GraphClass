#include "graphLista.h"


GraphList::GraphList()
{
	graph = NULL
}

int GraphList::loadGraph(string path,string output = "./graphInfo.txt"){
	string line;
	int nVertices,x,y,mEdges;
	float d_medio; //(sum of all degrees)/number of vertices()
	
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;
	
	ifstream file (path , ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &n);
	
	graph = new linkedList[n];
	int vertDegree[nVertices];//for each vertex, store it's degree
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it

	for (int i = 0; i<n; i++){
			graph[i]=new linkedList;
	}

	while (!file.eof()){
		getline(file,line);
		sscanf(line.c_str(), "%d %d", &x, &y);
		graph[x-1].insert(y-1);
		graph[y-1].insert(x-1);
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
	}

	file.close();
	
	for (int j = 0; j<nVerices; j++){
		degrees[vertDegree[j]]++;
	}


	string degreeString;
	for (j= 0; j<nVertices; j++){
		degreeString+=to_string(j)+to_string(degrees[j]/nVerices)+"\n";
	}	

	d_medio = d_medio/nVertices;

	ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<endl;



}
