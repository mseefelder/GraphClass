#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

int main()
{
	string line;
	int n,x,y;
	char * value = NULL;
	vector<bool> bitMatrix;
	//bool** graphMatrix;
	ifstream file ("as_graph.txt",ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &n);
	if (true){
		//graphMatrix= new bool*[n-1];
		bitMatrix.resize(n*n, false);
		/*for ( int i = 0; i< n-1; i++){
			//graphMatrix[i] = new bool [n-1];
			for( int j = 0 ; j < n-1 ; j++){
				//graphMatrix[i][j] = false;
				cout<<bitMatrix[1*n+1]<<endl;
			}
		}*/	
		while (!file.eof()){
			getline(file,line);
			//if (value) delete value;
			//value = strtok(line.c_str()," ");
			//x = atoi(value);
			//delete value;
			//value = strtok(line.c_str()," ");
			//y = atoi(value);
			sscanf(line.c_str(), "%d %d", &x, &y);
			//graphMatrix[y][x] = true;
			x--;
			y--;
			bitMatrix[x*n+y] = true;
			bitMatrix[y*n+x] = true;
			//graphMatrix[y][x] = true;
		}
	}
	
	cout<<bitMatrix[9*n+249]<<endl;

}
	
