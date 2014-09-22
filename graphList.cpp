#include "graphList.h"



bool GraphList::compareByLength(const CComp &a, const CComp &b)
{
    return a.size < b.size;
}

int GraphList::loadGraph(std::string path,std::string output){
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

	return 1;

}

int GraphList::BFS(int inicial, std::string path){
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
			line = fifo.front();
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
		vertexString+= "V: "+std::to_string(j+1)+" Pai: "+std::to_string(parents[j]+1)+" Nivel: "+std::to_string(levels[j])+"\n";
	}	

	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Resultado da BFS: \n"<<vertexString<<std::endl;
	outFile.close();
	
	delete [] parents; delete [] levels;

	return 1;

}

int GraphList::DFS(int inicial, std::string path){
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

int GraphList::connectedComponents(){
	std::cout<<">>||"<<std::endl;
	int nComponents = 0 ;//vai contar o número de componentes
	 
	//para armazenar pares de <elemento por onde comecei a bfs, tamanho da componente conexa>
	std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >,CompareDist > myHeap;
	
	bool* vertices;
	vertices = new bool[nVertices];//vai marcar quem já ta em alguma CC
	std::queue<int> fifo;
	int line;
	int size = 0;
	
	for(int x = 0;x<nVertices;x++){
		vertices[x] = false;//pra primeira BFS, começa tudo falso
	}
	std::cout<<"1BFS"<<std::endl;
	//Primeira BFS, pega pra cada componente o vertice inicial e o tamanho
	for(int i = 0;i<nVertices;i++){
		size = 0;
		if(vertices[i]==false){
			fifo.push(i);
			vertices[i] = true;
			size++;
			nComponents++;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (vertices[*it]==false){//nessa primeira BFS só olha os vertices que ainda estão false
						fifo.push(*it);
						vertices[*it] = true;
						size++;
					}
				}
			fifo.pop();
			}
		myHeap.emplace(i,size);//a heap bota no topo a maior componente (ordena pelo size).
		}
	}
	std::cout<<"1BFS-end"<<std::endl;
	//IMPORTANTE: Agora, no vertices[], todos os elementos são true. 
	//Pra proxima BFS vamos usar true como ainda nao marcado e false como marcado
	
	int counter = 0;//Em cada loop interno vai conar em que posicao do array da CC estamos colocando o elemento 
	int vertice = 0;//Vamos guardar o elemento por onde começamos
	
	int** ccOrder;//array de arrays para guardar todas as componentes conexas.
	ccOrder = new int*[nComponents];
	
	std::cout<<"2BFS"<<std::endl;
	for(int i = 0;i<nComponents;i++){
		counter = 2;
		size = myHeap.top().second;
		ccOrder[i] = new int[size+1];//aloca tamanho size+1 pra colocar no elemento 0 qual o tamanho da
									//componente que ta vindo e depois insere os vertices todos
		vertice = myHeap.top().first;
		ccOrder[i][0] = size;//temos q colocar isso no arquivo e usar pra otimizar o loop de output
		ccOrder[i][1] = vertice+1;//bota o elemento que vai começar a BFS
		
		
		myHeap.pop();
		
		//rodo a BFS a partir do vertice e aloco na array da componente conexa dele
		fifo.push(vertice);
		vertices[vertice] = false;
		while(!fifo.empty()){
			line = fifo.front();
			for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
				if (vertices[*it]==true){
					fifo.push(*it);
					vertices[*it] = false;
					ccOrder[i][counter] = *it+1;
					counter++;
				}
			}
		fifo.pop();
		}
	}
	std::cout<<"2BFS-end"<<std::endl;
	
	//printo
	std::string path = "results/connectedComp-matrix.txt";
	std::ofstream outFile;
	outFile.open(path);
	outFile<<"Componentes conexas: \n";
	outFile<<nComponents<<"\n";
	for (int j=0;j<nComponents;j++){
		size = ccOrder[j][0];
		outFile<<"Componente #"<<j<<" - Tamanho: "<<size<<"\n";
		for (int i = 1; i<size+1; i++){
			outFile<<ccOrder[j][i]<<", ";
		}
		outFile<<"\n";
		delete [] ccOrder[j];
	}
	outFile<<std::endl;
	outFile.close();

	delete [] vertices; delete [] ccOrder;
	
	return 1;
}

int GraphList::Diameter(int b, int e){
	 int begin = b;
	 int end = e;
	 
	std::cout<<"Starting Diameter(): "<<begin<<" -> "<<end<<std::endl;
	int diameter = 0;

	int threadN = omp_get_max_threads();
	std::cout<<threadN<<std::endl;
	
	int* diameters;
	diameters = new int[threadN];
	
	int** levels;
	levels = new int*[threadN];
	for(int i = 0; i<threadN; i++){
		levels[i] = new int[nVertices];
		diameters[i] = 0;
	}
	
	#pragma omp parallel
   	{
   		for(int x = 0; x<nVertices; x++)
			levels[omp_get_thread_num()][x] = -1;
	}
	
	std::queue<int>* fifo;
	fifo = new std::queue<int>[threadN];
	
	std::cout<<"Setup done!"<<std::endl;
	
#pragma omp parallel
   	{
//////////////A partir daqui tem uma cópia em cada thread, rodando
   	int thread = omp_get_thread_num();
	int line = 0;
	int localDiameter = 0;
	
	//Primeira BFS, pega pra cada componente o vertice inicial e o tamanho
#pragma omp for
////////--------------------------------------Esse for e dividido entre os threads
	for(int i = begin;i<end;i++){//for(int i = 0;i<nVertices;i++){
			
			for(int x = 0; x<nVertices; x++){
				levels[thread][x] = -1;}
				
			fifo[thread].push(i);
			levels[thread][i] = 0;
			localDiameter = -1;
			
			while(!fifo[thread].empty()){
				line = fifo[thread].front(); //fifo.pop() <--removes the object and returns void
				
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					
					if (levels[thread][*it]==-1){
						
						fifo[thread].push(*it);
						levels[thread][*it]=levels[thread][line]+1;
						if(levels[thread][*it]>localDiameter) localDiameter = levels[thread][*it];
						
					}
				
				}
			
			fifo[thread].pop();
			
			}
			if(localDiameter>diameters[thread]) diameters[thread] = localDiameter;
////////--------------------------------------
	}

//////////////
	}
	
	for(int j = 0; j<threadN; j++){
		if(diameters[j]>diameter) diameter = diameters[j];
	}
	
	std::cout<<"\n ---"<<diameter<<"---\n"<<std::endl;
	return diameter;
	
}

/*
//non-parallell
int GraphList::Diameter(){
	int diameter = 0;
	
	int* vertices;
	vertices = new int[nVertices];
	
	int* levels;
	levels = new int[nVertices];
	for(int x = 0;x<nVertices;x++){
		vertices[x] = -1;//pra primeira BFS, começa tudo falso
		levels[x] = -1;
	}
	
	std::queue<int> fifo;
	
	int line = 0;
	int localDiameter = 0;
	
	std::cout<<"1BFS"<<std::endl;
	//Primeira BFS, pega pra cada componente o vertice inicial e o tamanho
	for(int i = 0;i<nVertices;i++){
		
			fifo.push(i);
			vertices[i] = i;
			levels[i] = 0;
			localDiameter = -1;
			while(!fifo.empty()){
				line = fifo.front(); //fifo.pop() <--removes the object and returns void
				localDiameter++;
				for (auto it = graph[line].begin(); it != graph[line].end(); ++it){
					if (vertices[*it]!=(i)){//nessa primeira BFS só olha os vertices que ainda estão false
						fifo.push(*it);
						vertices[*it] = i;
						levels[*it]=levels[line]+1;
						if(levels[*it]>localDiameter) localDiameter = levels[*it];
					}
				}
			fifo.pop();
			}
			if(localDiameter>diameter) diameter = localDiameter;
	}
	
	std::cout<<diameter<<std::endl;
	return diameter;
	
}
*/

