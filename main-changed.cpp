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

	/*
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
	
	int tamanho = lista->getSize();
	int listaJunta[tamanho];
	lista->list2Array(listaJunta);
	for(int m=0; m<tamanho; m++) cout<<"ELEMENTO:"<<listaJunta[m]<<endl;
	*/
	linkedList** graph;
	string line;
	int nVertices,x,y,mEdges;
	float d_medio; //(sum of all degrees)/number of vertices()
	
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;
	
	ifstream file ("as_graph.txt" , ios::in|ios::binary);
	getline (file,line);
	sscanf(line.c_str(), "%d", &nVertices);
	cout<<nVertices<<"\n";
	linkedList* grafo;
	grafo = new linkedList[nVertices];
	graph = &grafo; 
	int vertDegree[nVertices];//for each vertex, store it's degree
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it

	//for (int i = 0; i<nVertices; i++){
	//	graph[i] = new linkedList();
	//}
	cout<<"initialized!"<<endl;
	while (!file.eof()){
		getline(file,line);
		sscanf(line.c_str(), "%d %d", &x, &y);
		cout<<"line scanned \n";
		if ((graph[0])->insert(1)==-1){
				cout<<"deu ruim!"<<endl;
				return -1;
		}
		cout<<"Teste:"<<graph[0]->listAll()[0]<<"\n";
		for(int i = 0; i<nVertices; i++){
				graph[i]->insert(1);
				cout<<"Tá bom:"<<i<<"\n";
		}
		cout<<"No error until now... \n";
		graph[x-1]->insert(y-1);
		cout<<"[x-1] and no error \n";
		graph[y-1]->insert(x-1);
		cout<<"[y-1] and no error \n";
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
	for (int j= 0; j<nVertices; j++){
		degreeString+= std::to_string(j) + std::to_string(degrees[j]/nVertices) + "\n"; //when compiling, set flag -std=c++11
	}	

	d_medio = d_medio/nVertices;

	ofstream outFile;
	outFile.open("log_bolado.txt");
	outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<endl;

	
	return 1;
}
	