#include "graph.h"

int Graph::buildGraph(std::string path,std::string output){
	std::string line;
	int x,y,mEdges;
	float d_medio; //(sum of all degrees)/number of vertices()

	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;

	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::getline (file,line);//discards the first line

	//Check whether matrix is weighted or not
	int count=0, size;
	std::getline(file,line);
	size = line.size();
	for(int x=0; x<size; x++)
	{
		if(line.substr(x,1) == " ") count++;
	}

	file.close();

	//Instantiate
	if(count == 1){
		weighted = false;
		if (isList){
			graph = new GraphData(&path, &output);
		}
		else{
			//graph = new GraphData<matrix> (&path, &output);
		}
	}
	else if (count == 2){
		weighted = true;
		if (isList){
			//graph = new GraphData<Wlist> (&path, &output);
		}
		else{
			//graph = new GraphData<Wmatrix> (&path, &output);
		}
	}

	/*

	if(graph) delete [] graph;
	graph = new std::forward_list<int>[nVertices];

	int* vertDegree;
	vertDegree = new int[nVertices];//for each vertex, store it's degree
	for (int i = 0; i<nVertices; i++){
			vertDegree[i]=0;
	}

	int* degrees;
	degrees = new int[nVertices-1]; //for each degree, indicate # of vertices that has it
	for (int i = 0; i<(nVertices-1); i++){
			degrees[i]=0;
	}

	std::getline(file,line);
	while (!file.eof()){
		std::sscanf(line.c_str(), "%d %d", &x, &y);
		x--; y--;
		graph[x].push_front(y);
		graph[y].push_front(x);
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		d_medio+=2.0;
		std::getline(file,line);
	}

	file.close();
	int maxDegree = 0;
	for (int j = 0; j<nVertices; j++){
		degrees[vertDegree[j]]++;
		if(vertDegree[j]>maxDegree) maxDegree = vertDegree[j];
	}

	std::string degreeString;
	float temp = 0.0;
	for (int j= 0; j<maxDegree; j++){
		temp = ((float)degrees[j]/nVertices);
		degreeString+="Degree:"+std::to_string(j)+" --> "+std::to_string(temp)+"\n";
	}

	d_medio = d_medio/nVertices;

	std::ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;

	delete [] degrees; delete [] vertDegree;

	*/
	return 1;

}
