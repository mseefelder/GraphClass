#include "graphLista.h"


GraphList::GraphList()
{
	graph = NULL
}

int GraphList::loadGraph(string path){
	string line;
	int n,x,y;
	char * value = NULL;
	ifstream file (path , ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &n);
	graph= new linkedList[n];
	
	while (!file.eof()){
		getline(file,line);
		sscanf(line.c_str(), "%d %d", &x, &y);
	}



}
