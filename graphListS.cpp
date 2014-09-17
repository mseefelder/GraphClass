#include "graphListS.h"

int GraphListS::loadGraph(std::string path,std::string output){// = "./graphInfo.txt"){
	std::string line;
	int x,y,mEdges;
	float d_medio; //(sum of all degrees)/number of vertices()
	
	mEdges = 0;
	d_medio = 0.0;
	char * value = NULL;

	std::ifstream file;
	file.open(path, std::ifstream::in);
	std::getline (file,line);
	std::sscanf(line.c_str(), "%d", &nVertices);
	
	std::cout<<"Vertices:  "<<nVertices<<"\n";	

	graph = new std::forward_list<int>[nVertices];

	std::cout<<"Stayin' alive \n";

	int vertDegree[nVertices];//for each vertex, store it's degree
	for (int i = 0; i<nVertices; i++){
			vertDegree[i]=0;
	}
	int degrees[nVertices-1]; //for each degree, indicate # of vertices that has it
	
	for (int i = 0; i<(nVertices-1); i++){
			degrees[i]=0;
	}
	
	std::cout<<"Before while: ";	
	std::getline(file,line);
	while (!file.eof()){
		std::cout<<"-";
		//getline(file,line);
		std::sscanf(line.c_str(), "%d %d", &x, &y);
		x--; y--;
		//std::cout<<"Verts: "<<x<<" - "<<y<<"\n";
		graph[x].push_front(y);
		graph[y].push_front(x);
		//std::cout<<"Foi! \n";
		mEdges++;
		vertDegree[x]++;
		vertDegree[y]++;
		//std::cout<<"Degrees foi! \n";
		d_medio+=2.0;
		std::getline(file,line);
		std::cout<<".";
	}

	file.close();
	
	std::cout<<"\n";
	std::cout<<"Arquivo lido! \n";
	for (int j = 0; j<nVertices; j++){
		//std::cout<<"Vert: "<<j+1<<" Degree: "<<vertDegree[j]<<":";
		degrees[vertDegree[j]]++;
		//std::cout<<"Works! \n";
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

int GraphListS::BFS(int inicial, std::string path){// = "./graphBFS.txt"){
	inicial = inicial -1;

	//std::cout<<"Tamanho da bitmatrix:"<<bitMatrix->size()<<"\n";
	std::queue<int> fifo;
	//bool visited[nVertices]; //we can use vector<bool>
	int parents[nVertices];
	int levels[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			//visited[i]=false;
			parents[i]=-2;
			levels[i]=-1;
	}
	//visited[inicial]=true;
	parents[inicial]=-1;
	levels[inicial]=0;
	fifo.push(inicial);
	
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			//std::cout<<".";
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
			
//			for (int column = 0; column<nVertices; column++){
//					if (bitMatrix[elementIndex]==true){
//						//if (!visited[column]){
//						if (parents[column]==-2){
//							//visited[column]=true;
//							fifo.push(column);
//							parents[column]=(line);//parece certo
//							levels[column]=levels[line]+1;//parece certo
//						}
//					}
//			}
			for ( auto it = graph[line].begin(); it != graph[line].end(); ++it ){
				if (parents[*it]==-2){
					fifo.push(*it);
					parents[*it]=line;
					levels[*it]=levels[line]+1;
				}
			}
			
			
			fifo.pop();

	}
	std::string vertexString;
	for (int j= 0; j<nVertices; j++){
		vertexString+= "V: "+std::to_string(j+1)+"Pai: "+std::to_string(parents[j]+1)+"Nivel: "+std::to_string(levels[j])+"\n";
	}	

	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da BFS: \n"<<vertexString<<std::endl;
	outFile.close();

	return 1;

}
int GraphListS::DFS(int inicial, std::string path){
	inicial = inicial -1;
	std::stack<int> lifo;
	int parents[nVertices];
	int levels[nVertices];
	for (int i = 0; i<nVertices;i++){
		parents[i] = -2;
		levels[i] = -1;
	}
	parents[inicial] = -1;
	levels[inicial] = 0;
	lifo.push(inicial);

	int line = 0;
	int elementIndex = 0;
	while(!lifo.empty()){
		line = lifo.top();
		lifo.pop();
		
//		for (int column = 0; column<nVertices;column++){
//			if (line>column){
//				elementIndex = (((line+1)*line)/2)-(line)+column;}
//			else {
//				elementIndex = (((column+1)*column)/2)-(column)+line;}
//			if (bitMatrix[elementIndex] == true){
//				if (parents[column]==-2){
//					lifo.push(column);
//					parents[column] = line;
//					levels[column] = levels[line] +1;
//				}
//			}
//		}

		for ( auto it = graph[line].begin(); it != graph[line].end(); ++it ){
				if (parents[*it]==-2){
					lifo.push(*it);
					parents[*it]=line;
					levels[*it]=levels[line]+1;
				}
			}

	}
	
	std::string vertexString;
	for (int j= 0; j<nVertices; j++){
		vertexString+= "V: "+std::to_string(j+1)+" Pai: "+std::to_string(parents[j]+1)+" Nivel: "+std::to_string(levels[j])+"\n";
	}	

	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da DFS: \n"<<vertexString<<std::endl;
	outFile.close();

	return 1;
}
int GraphListS::connectedComponents(){
	int nComponents = 1 ;
	int edges[nVertices];
	std::queue<int> fifo;
	int line;
	int elementIndex;
	for(int x = 0;x<nVertices;x++){
		edges[x] = 0;
	}
	for(int i = 0;i<nVertices;i++){
		if(edges[i]==0){
			fifo.push(i);
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (edges[*it]==0){
						fifo.push(*it);
						edges[*it] = nComponents;
					}
				}
			fifo.pop();
			}
		nComponents += 1;
		}
	}
	for (int j=0;j<nVertices;j++){
		std::cout<<edges[j]<< "\n";
	}
	return 1;
}
