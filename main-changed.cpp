#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstring>
#include"linkedlist.h"
using namespace std;

int main()
{
	/*
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
	*/

	linkedList* lista;
	lista = new linkedList;
	lista->insert(1);
	lista->insert(3);
	lista->insert(5);
	lista->listAllS();
	lista->del(0);
	lista->listAllS();
	lista->insert(23);
	lista->listAllS();
	lista->del(2);
	lista->listAllS();
	lista->insert(32);
	lista->insert(44);
	lista->insert(1234567890);
	lista->listAllS();

	//delete lista;
	for(int n = 0; n<lista->getSize(); n++) cout<<lista->listAll()[n]<<endl;
	int* minhalista;
	minhalista = lista->listAll();
	for(int m=0; m<lista->getSize(); m++) cout<<minhalista[m]<<endl;
	int tamanho = lista->getSize();
	int* listaJunta;
	lista->list2Array(listaJunta);
	for(int m=0; m<tamanho; m++) cout<<listaJunta[m]<<endl;
	return 1;
}
	
