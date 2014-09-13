#include "graphMatrix.h"


GraphMatrix::GraphMatrix()
{
	graph = NULL
}

int GraphMatrix::loadGraph(string path,string output = "./graphInfo.txt"){
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
	ifstream file (path , ios::in|ios::binary);
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
		bitMatrix[x*n+y] = true;
		bitMatrix[y*n+x] = true;// redundance
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
	for (j= 0; j<nVertices; j++){
		degreeString+= std::to_string(j)+std::to_string(degrees[j]/(float)nVerices)+"\n";
	}	

	d_medio = d_medio/nVertices;

	ofstream outFile;
	outFile.open(output);
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<endl;
	outFile.close;
}
