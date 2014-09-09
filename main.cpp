#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
	string line;
	int n,x,y;
	char * value = NULL;
	bool** graphMatrix;
	ifstream file ("as_graph.txt",ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &n);
	if (true){
		graphMatrix= new bool*[n-1];
		for ( int i = 0; i< n-1; i++){
			graphMatrix[i] = new bool [n-1-i];
			for( int j = 0 ; j < n-1-i ; j++){
				graphMatrix[i][j] = false;
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
			if (y > x) graphMatrix[x][y] = true;
			else graphMatrix[y][x] = true;
		}
	}
	
	cout<<graphMatrix[5][6]<<graphMatrix[10][250]<<endl;

}
	
