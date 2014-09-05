#include "graph.h"


Graph::Graph()
{
}

int Graph::loadGraph(string path, int type){
	string line;
	int n,x,y;
	char * value = NULL;
	ifstream file (path , ios::in|ios::binary);
	getline (file,line);
	n = atoi(line.c_str());
	if (type == 0 ){
		graphMatrix= new bool*[n-1];
		for ( int i = 0; i< n-1; i++){
			graphMatrix[i] = new bool [n-1-i];
			for( int j = 0 ; j < n-1-i ; j++){
				graphMatrix[i][j] = false;
			}
		}	
		while (!file.eof()){
			getline(file,line);
			if (value) delete value;
			value = strtok(line," ");
			x = atoi(value);
			delete value;
			value = strtok(line," ");
			y = atoi(value);
			if (y > x) graphMatrix[x][y] = true;
			else graphMatrix[y][x] = true;
		}
	}
	if (type == 1){
		cout << "tarcos"<< endl;
	}



}
