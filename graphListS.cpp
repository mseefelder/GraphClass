#include "graphListS.h"

bool GraphListS::compareByLength(const CComp &a, const CComp &b)
{
    return a.size < b.size;
}

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
		//std::cout<<"-";
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
		//std::cout<<".";
	}

	file.close();
	int maxDegree = 0;
	for (int j = 0; j<nVertices; j++){
		//std::cout<<"Vert: "<<j+1<<" Degree: "<<vertDegree[j]<<":";
		degrees[vertDegree[j]]++;
		if(vertDegree[j]>maxDegree) maxDegree = vertDegree[j];
		//std::cout<<"Works! \n";
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

	return 1;

}

int GraphListS::BFS(int inicial, std::string path){// = "./graphBFS.txt"){
	inicial = inicial -1;

	std::queue<int> fifo;
	int* parents;
	parents = new int[nVertices];
	int* levels;
	levels = new int[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			parents[i]=-2;
			levels[i]=-1;
	}
	parents[inicial]=-1;
	levels[inicial]=0;
	fifo.push(inicial);
	
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
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
	
	delete [] parents; delete [] levels;

	return 1;

}
int GraphListS::DFS(int inicial, std::string path){
	inicial = inicial -1;
	std::stack<int> lifo;
	int* parents;
	parents = new int[nVertices];
	int* levels;
	levels = new int[nVertices];

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
	
	delete [] parents; delete [] levels;

	return 1;
}
/*//funciona é rapido mas não faz o que queremos
int GraphListS::connectedComponents(){
	int nComponents = 0 ;
	int* edges;
	edges = new int[nVertices];
	std::queue<int> fifo;
	int line;
	int elementIndex;
	
	for(int x = 0;x<nVertices;x++){
		edges[x] = -1;
	}
	
	for(int i = 0;i<nVertices;i++){
		if(edges[i]==-1){
			fifo.push(i);
			edges[i] = nComponents;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (edges[*it]==-1){
						fifo.push(*it);
						edges[*it] = nComponents;
					}
				}
			fifo.pop();
			}
		nComponents += 1;
		}
	}
	
	std::string caminhao = "results/ConnectedComp.txt";
	std::ofstream outFile;
	outFile.open(caminhao);
	outFile<<"Componentes conexas: \n";
	for (int j=0;j<nVertices;j++){
		outFile<<edges[j]<< " - ";
	}
	outFile<<std::endl;
	outFile.close();

	delete [] edges;
	
	return 1;
}
*/

/*//Funciona e chama a BFS: Muito devagar
int GraphListS::connectedComponents(){
	int nComponents = 0 ;
	bool* edges;
	edges = new bool[nVertices];
	std::queue<int> fifo;
	std::vector<CComp*> allCC;
	//std::list<CComp> allCC;
	int line;
	int elementIndex;
	for(int x = 0;x<nVertices;x++){
		edges[x] = false;
	}
	for(int i = 0;i<nVertices;i++){
		if(edges[i]==false){
			std::cout<<"bfs:"<<std::endl;
			allCC.push_back(BFS_R(i, edges));
			nComponents++;
		}
	}
	
	//allCC.sort*(allCC.begin(), allCC.end(), compareByLength);
	std::cout<<"calculado"<<std::endl;
	
	std::string caminhao = "results/ConnectedComp.txt";
	std::ofstream outFile;
	outFile.open(caminhao);
	outFile<<"Componentes conexas: \n";
	for (int j=0;j<nComponents;j++){
		outFile<<"Componente #"<<j<<"\n";
		for(int i=0; i<allCC[j]->size; i++){
			outFile<<allCC[j]->vertices[i]<<", ";
		}
		outFile<<"\n \n";
	}
	outFile<<std::endl;
	outFile.close();
	
	delete [] edges;
	
	return 1;
}
*/

//igual a a que chama a BFS, mas tá com a BFSescrita inline
int GraphListS::connectedComponents(){
	int nComponents = 0 ;
	bool* vertices;
	vertices = new bool[nVertices];
	std::queue<int> fifo;
	std::vector<CComp*> allCC;
	
	CComp* localComp = NULL;
	bool* belongs = NULL;
	int inicial = 0;
	
	//std::list<CComp> allCC;
	int line;
	int elementIndex;
	for(int x = 0;x<nVertices;x++){
		vertices[x] = false;
	}
	for(int i = 0;i<nVertices;i++){
		if(vertices[i]==false){
			//std::cout<<"bfs:"<<std::endl;
			
			inicial = i;
	localComp = new CComp();
	std::queue<int> fifo;
	belongs = new bool[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			belongs[i]=false;
	}
	belongs[inicial]=true;
	fifo.push(inicial);
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
			localComp->size++;
			for ( auto oob = graph[line].begin(); oob != graph[line].end(); ++oob ){
				if (belongs[*oob]==false){
					fifo.push(*oob);
					belongs[*oob]=true;
					vertices[*oob]=true;
				}
			}
			fifo.pop();
	}
	
	localComp->vertices = new int[localComp->size];
	
	int counter = 0;
	for (int j= 0; j<nVertices; j++){
		if(belongs[j]){
			
			localComp->vertices[counter] = j;//"V: "+std::to_string(j+1)+"Pai: "+std::to_string(parents[j]+1)+"Nivel: "+std::to_string(levels[j])+"\n";
			counter++;
		}
		
	}
	
	delete [] belongs;
			
			nComponents++;
			allCC.push_back(localComp);
		}
	}
	
	//allCC.sort*(allCC.begin(), allCC.end(), compareByLength);
	std::cout<<"calculado"<<std::endl;
	
	std::string caminhao = "results/ConnectedComp.txt";
	std::ofstream outFile;
	outFile.open(caminhao);
	outFile<<"Componentes conexas: \n";
	for (int j=0;j<nComponents;j++){
		outFile<<"Componente #"<<j<<"\n";
		for(int i=0; i<allCC[j]->size; i++){
			outFile<<allCC[j]->vertices[i]<<", ";
		}
		outFile<<"\n \n";
	}
	outFile<<std::endl;
	outFile.close();
	
	delete [] vertices;
	
	return 1;
}

CComp* GraphListS::BFS_R(int inicial, bool* vertices){// = "./graphBFS.txt"){
	inicial = inicial;
	CComp* localComp;
	localComp = new CComp();
	std::queue<int> fifo;
	bool* belongs;
	belongs = new bool[nVertices];
	for (int i  = 0; i<nVertices; i++){ 
			belongs[i]=false;
	}
	belongs[inicial]=true;
	fifo.push(inicial);
	int line = 0;
	int elementIndex=0;
	while(!fifo.empty()){
			line = fifo.front(); //fifo.pop() <--removes the object and returns void
			localComp->size++;
			for ( auto oob = graph[line].begin(); oob != graph[line].end(); ++oob ){
				if (belongs[*oob]==false){
					fifo.push(*oob);
					belongs[*oob]=true;
					vertices[*oob]=true;
				}
			}
			fifo.pop();
	}
	
	localComp->vertices = new int[localComp->size];
	
	int counter = 0;
	for (int j= 0; j<nVertices; j++){
		if(belongs[j]){
			
			localComp->vertices[counter] = j;//"V: "+std::to_string(j+1)+"Pai: "+std::to_string(parents[j]+1)+"Nivel: "+std::to_string(levels[j])+"\n";
			counter++;
		}
		
	}
	
	delete [] belongs;

	return localComp;

}

/*//pode ser q seja essa a que funciona
int GraphListS::connectedComponents(){
	int nComponents = 0 ;
	bool* vertices;
	vertices = new bool[nVertices];
	std::queue<int> fifo;
	std::vector<int> firstIndices;
	int line;
	int elementIndex;
	
	for(int x = 0;x<nVertices;x++){
		edges[x] = false;
	}
	
	for(int i = 0;i<nVertices;i++){
		if(edges[i]==false){
			fifo.push(i);
			firstIndices.push_back();
			edges[i] = nComponents;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (edges[*it]==-1){
						fifo.push(*it);
						edges[*it] = true;
					}
				}
			fifo.pop();
			}
		nComponents += 1;
		}
	}
	
	std::string caminhao = "results/ConnectedComp.txt";
	std::ofstream outFile;
	outFile.open(caminhao);
	outFile<<"Componentes conexas: \n";
	for (int j=0;j<nVertices;j++){
		outFile<<edges[j]<< " - ";
	}
	outFile<<std::endl;
	outFile.close();

	delete [] edges;
	
	return 1;
}



int GraphListS::connectedComponents(){
	int nComponents = 0;
	std::vector<int>* allComponents;
	
	int* vertices;
	vertices = new int[nVertices];
	
	int* cComponents;
	cComponents = new int[nVertices];
	
	std::queue<int> fifo;
	std::forward_list<int> ccSizes;
	
	int line, size; line = 0; size = 0;
	
	for(int x = 0;x<nVertices;x++){
		vertices[x] = -1;
		cComponents[x] = 0;
	}
	
	for(int i = 0;i<nVertices;i++){
		if(vertices[i]==(-1)){
			fifo.push(i);
			vertices[i] = nComponents;
			size = 1;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (vertices[*it]==-1){
						fifo.push(*it);
						vertices[*it] = nComponents;
						size++;
					}
				}
			fifo.pop();
			}
			nComponents += 1;
			std::cout<<size<<" "<<nComponents<<"\n";
			cComponents[nComponents] = size;
			ccSizes.push_front(size);
			std::cout<<size;
		}
	}
	
	ccSizes.sort(std::greater<int>());
	
	size = 0;
	allComponents = new std::vector<int>[nComponents];
	for(int i =0; i<nComponents; i++){
		allComponents[i].resize(cComponents[i]);
	}
	for(int i = 0; i<nVertices; i++){
		allComponents[vertices[i]].push_back(i);
	}
	
	std::string caminhao = "results/ConnectedComp.txt";
	std::ofstream outFile;
	outFile.open(caminhao);
	outFile<<"Componentes conexas: \n";
	
	for(int i=0; i<nComponents; i++){
		outFile<<"CC: "<<i<<"\n Size = "<<cComponents[i+1]<<"\n";
	}

	
	
//	std::string caminhao = "results/ConnectedComp.txt";
//	std::ofstream outFile;
//	outFile.open(caminhao);
//	outFile<<"Componentes conexas: \n";
//	size = 0;
//	int currentIndex = 0;
//	for(int i=0; i<nComponents; i++){
//		outFile<<"\n";
//		size = ccSizes.front();
//		ccSizes.pop_front();
//		for(int j = 0; j<nComponents; j++){
//			if(cComponents[j] == size)
//				currentIndex = j;
//				cComponents[j] = -1;
//		}
//		outFile<<"Connected Component "<<i<<": \n Size:"<<size<<"\n Vertices: \n";
//		for (int k = 0; k<nVertices; k++){
//			if(vertices[k] == i) 
//				outFile<<k<<", ";
//		}
//	}
//	outFile<<std::endl;
//	outFile.close();


	delete [] vertices; delete [] cComponents;
	
	return 1;
}

int GraphListS::connectedComponents(){
	int nComponents = 0;
	
	int* vertices;
	vertices = new int[nVertices];
	
	std::vector<int>* survivors;
	survivors = new std::vector(nVertices);
	int counter = 0;
	for ( auto it = survivors.begin(); it != survivors.end(); ++it ){
		survivors[counter] = counter;
		counter++
	}
	
	std::queue<int> fifo;
	std::forward_list<int> ccSizes;
	
	int line, size; line = 0; size = 0;
	
	for(int x = 0;x<nVertices;x++){
		vertices[x] = -1;
		cComponents[x] = 0;
	}
	
	for(int i = 0;i<nVertices;i++){
		if(vertices[i]==(-1)){
			BFS_R(i, nComponents, survivors);
			nComponents++;
		}
	}
}


*/
