#include "graph.h"
#include "iostream"
#include "string"

template<class T> void Graph<T>::buildGraph(std::string path,std::string output){

  //Line used to parse the graph file
  std::string line;
  //(sum of all degrees)/number of vertices()
  float mean_degree = 0.0;
  //number of edges on the graph
  int mEdges = 0;

  //Open graph file:------------------------------------------------------------
  std::ifstream file;
  file.open(path, std::ifstream::in);
  std::getline (file,line);
  std::sscanf(line.c_str(), "%d", &nVertices);

  //Check whether matrix is weighted or not-------------------------------------
  int count=0, size;
  std::getline(file,line);
  size = line.size();
  for(int i=0; i<size; i++)
  {
    if(line.substr(i,1) == " ") count++;
  }

  //Sets weighted flag
  if(count == 1) weighted = false;
  else if (count == 2) weighted = true;

  file.close();

  //Instantiate-----------------------------------------------------------------

  graph.generate(nVertices);//WE HAVE TO IMPLEMENT THIS

  //Auxiliary structures--------------------------------------------------------
  //stores each vertex: it's degree
  int* vertDegree;
  vertDegree = new int[nVertices];
  for (int i = 0; i<nVertices; i++){
      vertDegree[i]=0;
  }

  //stores for each degree: the # of vertices that has it
  int* degrees;
  degrees = new int[nVertices-1];
  for (int i = 0; i<(nVertices-1); i++){
      degrees[i]=0;
  }

  //Begin graph filling:--------------------------------------------------------
  int x,y;
  float weight;
  //Procedure to fill a weighted Graph
  //std::ifstream file;
  file.open(path, std::ifstream::in);
  std::getline (file,line);//discard nVertices line

  if(weighted){
    //std::sscanf(line.c_str(), "%d %d %d", &x, &y, &weight);
    //graph.push(x,y,weight);
    std::getline(file,line);
    while (!file.eof()){
      std::sscanf(line.c_str(), "%d %d %f", &x, &y, &weight);
      //Correct vertex indexes
      x--; y--;
      //test all the edges for a value < 0
      if(weight<0) negativeWeight = true;
      //std::cout<<"   "<<x<<","<<y<<","<<weight<<std::endl;
      graph.push(x,y,weight);
      mEdges++;
      vertDegree[x]++;
      vertDegree[y]++;
      mean_degree+=2.0;
      std::getline(file,line);
    }
  }

  //Procedure to fill a non-weighted Graph
  else{
    //std::sscanf(line.c_str(), "%d %d", &x, &y);
    //graph.push(x,y,1);//WE HAVE TO IMPLEMENT THIS ON THE DATA STRUCTURE
    std::getline(file,line);
    while (!file.eof()){
      std::sscanf(line.c_str(), "%d %d", &x, &y);
      x--; y--;
      graph.push(x,y,1.0);
      mEdges++;
      vertDegree[x]++;
      vertDegree[y]++;
      mean_degree+=2.0;
      std::getline(file,line);
    }
  }
  //Finished reading graph, close file:
  file.close();

  //Graph analysis:-------------------------------------------------------------

  //Find the maximum degree:
  int maxDegree = 0;
  for (int j = 0; j<nVertices; j++){
    degrees[vertDegree[j]]++;
    if(vertDegree[j]>maxDegree) maxDegree = vertDegree[j];
  }

  //Prepare a string with empirical distribution of degrees
  std::string degreeString;
  float temp = 0.0;
  for (int j= 0; j<maxDegree; j++){
    temp = ((float)degrees[j]/nVertices);
    degreeString+="Degree:"+std::to_string(j)+" --> "+std::to_string(temp)+"\n";
  }

  //Compute mean degree
  mean_degree = mean_degree/nVertices;

  //Write file with graph analysis
  std::ofstream outFile;
  outFile.open(output);
  outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#mean_degree = "<<mean_degree<<"\n"<<degreeString<<std::endl;

  //Delete auxiliary structures so as to not leak memory
  delete [] degrees; delete [] vertDegree;

  graph.postProcess();//

  return;

}

template<class T> void Graph<T>::BFS(int initial, std::string output){
  //Correcting index
  initial = initial -1;

  //Auxiliary queue used during the algorithm
  std::queue<int> fifo;
  //For each vertex: store its parent
  int* parents;
  parents = new int[nVertices];
  //For each vertex: store its level
  int* levels;
  levels = new int[nVertices];
  //Fill arrays
  for (int i  = 0; i<nVertices; i++){
      parents[i]=-2;
      levels[i]=-1;
  }
  //Set initial values
  parents[initial]=-1;
  levels[initial]=0;
  fifo.push(initial);

  int current = 0;
  int* neig = NULL;
  int elementIndex=0;
  int iterations = 0;
  while(!fifo.empty()){
      current = fifo.front();
      iterations = graph.degree(current);
      graph.getNeighbours(current, &neig);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[neig[i]]==-2){
          fifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          levels[*(neig+i)]=levels[current]+1;
        }
      }

      delete [] neig;
      fifo.pop();
  }

  std::string vertexString;
  for (int j= 0; j<nVertices; j++){
    vertexString+= "V: "+std::to_string(j+1)+" Pai: "+std::to_string(parents[j]+1)+" Nivel: "+std::to_string(levels[j])+"\n";
  }

  std::ofstream outFile;
  outFile.open(output);
  outFile<<"Resultado da BFS: \n"<<vertexString<<std::endl;
  outFile.close();

  delete [] parents; delete [] levels;

  return;
}

template<class T> void Graph<T>::Dijkstra(int initial, std::string output){
 	//Correct inicial index
 	initial--;

 	//Store each element's parent
 	int* parents;
 	parents = new int[nVertices];

 	//Store each element's level
 	int* levels;
 	levels = new int[nVertices];

 	//Store each element's cost
 	float* cost;
 	cost = new float[nVertices];

 	int starter = 999999999;//very big float (gambiarra)
 	heap<float> pilha(nVertices,starter);

	//Initialize values
 	for(int i =0;i <nVertices;i++){
 		parents[i] = -2;
 		levels[i] = -1;
 		cost[i] = -1.0;
 	}

 	//Set values for initial vertex
 	pilha.replace(initial,0.0);
 	cost[initial] = 0.0;
 	parents[initial] = -1;
 	levels[initial] = 0;

 	//Auxiliar variables
 	int current;//vertex being computed
 	int iterations; //for each vertex, a different # of iterations
 	int* neig = NULL; //array to store neighbours
 	float* weig = NULL; //array to store weights

 	while(!pilha.empty()){
 		std::cout<<std::endl;
 		pilha.printTable();//Logs the weights in each element
 		pilha.printHeap();
 		current = pilha.top_index();//Gets the minimum value element
 		iterations = graph.degree(current);
 		graph.getNeighbours(current,&neig);
 		graph.getWeights(current,&weig);

 		for(int i =0;i < iterations; i++){

 			if(pilha.exists(neig[i])){

 				//std::cout<<"index:"<<neig[i]<<"; cost:"<<pilha.cost(neig[i]);
 				//std::cout<<"; current:"<<pilha.cost(current)<<"; weight:"<<weig[i];
 				//std::cout<<std::endl;

 				if(pilha.cost(neig[i])>(pilha.cost(current) + weig[i]) ){
 					parents[neig[i]] = current;
 					levels[neig[i]] = levels[current] + 1;
 					cost[neig[i]] = (pilha.cost(current) + weig[i]);

 					//std::cout<<"   "<<neig[i]<<","<<pilha.cost(current) + weig[i]<<std::endl;

 					pilha.replace( neig[i], (pilha.cost(current) + weig[i]) );
 				}

 			}

 		}

 		delete [] neig;
 		delete [] weig;
 		pilha.pop();
 	}

 	//Save the cost to get to each vertex from initial------------------------------------
 	int dijsize = 0;
 	std::string vertexString;
  for (int j= 0; j<nVertices; j++){
    if(!(parents[j]<-2)){
        vertexString+= std::to_string(j+1)+" "+std::to_string(cost[j])+" "+ +"\n";
        dijsize++;
    }
  }

  std::ofstream outFile;
  outFile.open(output);
  outFile<<dijsize<<"\n"<<vertexString<<"\b "<<std::endl;
  outFile.close();
  //-------------------------------------------------------------------------------------

	//deletes auxiliary arrays
  delete [] parents; delete [] levels; delete [] cost;

}
template<class T> void Graph<T>::Distance(int VertexA, int VertexB){
  int* parents;
  parents = new int[nVertices];
  std::string path;
  if (weighted == true && negativeWeight == false){
    float* distance;
    distance = new float[nVertices];
    Dijkstra_mod(VertexA,distance,parents);
    int counter;
    counter = parents[VertexB];
    while(parents[counter]!=0){
      path +=std::to_string(counter+1)+ ", "; // gambiarra para aparecer certo.
      counter = parents[counter];
  }
  std::cout<<"Distancia : " << distance[VertexB] <<" "<< "Caminho : " << path << std::endl;
  delete [] distance;
}
  else if(weighted == false){
    int* distance;
    distance = new int[nVertices];
    BFS_mod(VertexA,distance,parents);
    int counter;
    counter = parents[VertexB];
    while(parents[counter]!=0){
      path += ", " + std::to_string(counter);
      counter = parents[counter];
    }
    std::cout<<"Distancia : " << distance[VertexB] <<" "<< "Caminho : " << path << std::endl;
    delete [] distance;
  }

  delete [] parents;
;
  return;
}
template<class T> void Graph<T>::BFS_mod(int initial,int* distance, int* parents){
  //Correcting index
  initial = initial -1;

  //Auxiliary queue used during the algorithm
  std::queue<int> fifo;
  //For each vertex: store its parent
  //For each vertex: store its levelr
  //Fill arrays
  for (int i  = 0; i<nVertices; i++){
      parents[i]=-2;
  }
  //Set initial values
  parents[initial]=-1;
  distance[initial] = 0;
  fifo.push(initial);

  int current = 0;
  int* neig = NULL;
  int elementIndex=0;
  int iterations = 0;
  while(!fifo.empty()){
      current = fifo.front();
      iterations = graph.degree(current);
      graph.getNeighbours(current, &neig);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[neig[i]]==-2){
          fifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          distance[*(neig+i)] = distance[current]+1;
        }
      }

      delete [] neig;
      fifo.pop();
  }
  return;
}
template<class T> void Graph<T>::Dijkstra_mod(int initial,float* distance,int* parents){
  //Correct inicial index
  initial--;

  int starter = 999999999;//very big float (gambiarra)
  heap<float> pilha(nVertices,starter);

 //Initialize values
  for(int i =0;i <nVertices;i++){
    parents[i] = -2;
    distance[i] = -1.0;
  }

  //Set values for initial vertex
  pilha.replace(initial,0.0);
  distance[initial] = 0.0;
  parents[initial] = -1;

  //Auxiliar variables
  int current;//vertex being computed
  int iterations; //for each vertex, a different # of iterations
  int* neig = NULL; //array to store neighbours
  float* weig = NULL; //array to store weights

  while(!pilha.empty()){
    std::cout<<std::endl;
    pilha.printTable();//Logs the weights in each element
    pilha.printHeap();
    current = pilha.top_index();//Gets the minimum value element
    iterations = graph.degree(current);
    graph.getNeighbours(current,&neig);
    graph.getWeights(current,&weig);

    for(int i =0;i < iterations; i++){

      if(pilha.exists(neig[i])){
        if(pilha.cost(neig[i])>(pilha.cost(current) + weig[i]) ){
          parents[neig[i]] = current;
          distance[neig[i]] = (pilha.cost(current) + weig[i]);
          pilha.replace( neig[i], (pilha.cost(current) + weig[i]) );
        }
      }
    }

    delete [] neig;
    delete [] weig;
    pilha.pop();
  }
  return;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<class T> void Graph<T>::MST(int initial, std::string output){
 	//Correct inicial index
 	initial--;
 	
 	//Store each element's parent
 	int* parents;
 	parents = new int[nVertices];
 	
 	//Store each element's level
 	int* levels;
 	levels = new int[nVertices];
 	
 	//Store each element's cost
 	float* cost;
 	cost = new float[nVertices];
 
 	int starter = 999999999;//very big float (gambiarra)
 	heap<float> pilha(nVertices,starter);

	//Initialize values
 	for(int i =0;i <nVertices;i++){
 		parents[i] = -2;
 		levels[i] = -1;
 		cost[i] = -1.0;
 	}
 
 	//Set values for initial vertex
 	pilha.replace(initial,0.0);
 	cost[initial] = 0.0;
 	parents[initial] = -1;
 	levels[initial] = 0;
 	
 	//Auxiliar variables
 	int current;//vertex being computed
 	int iterations; //for each vertex, a different # of iterations
 	int* neig = NULL; //array to store neighbours
 	float* weig = NULL; //array to store weights
 	
 	while(!pilha.empty()){
 		std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------- \n";
 		std::cout<<std::endl;
 		pilha.printTable();//Logs the weights in each element
 		pilha.printHeap();
 		current = pilha.top_index();//Gets the minimum value element
 		iterations = graph.degree(current);
 		graph.getNeighbours(current,&neig);
 		graph.getWeights(current,&weig);
 		
 		pilha.pop();
 		
 		for(int i =0;i < iterations; i++){
 			std::cout<<"v:"<<current;for(int i=0; i<iterations; i++)std::cout<<" n:"<<neig[i];std::cout<<std::endl;
 			std::cout<<"exists("<<neig[i]<<")"<<std::endl;
 			if(pilha.exists(neig[i])){
 				
 				//std::cout<<"index:"<<neig[i]<<"; cost:"<<pilha.cost(neig[i]);
 				//std::cout<<"; current:"<<pilha.cost(current)<<"; weight:"<<weig[i];
 				//std::cout<<std::endl;
 				
 				if(pilha.cost(neig[i]) > weig[i] ){
 					parents[neig[i]] = current;
 					levels[neig[i]] = levels[current] + 1;
 					cost[neig[i]] = weig[i];
 					
 					std::cout<<"   >Replace ["<<neig[i]<<"] ,"<<weig[i]<<std::endl;
 					
 					pilha.replace( neig[i], weig[i] );
 				}
 				
 			}
 			
 		}
 		
 		//std::cout<<"Deleting..."<<std::endl;
 		delete [] neig;
 		delete [] weig;
 		
 		//std::cout<<"Before pop(): \n    ";
 		//pilha.printTable();
 		//std::cout<<"    ";
 		//pilha.printHeap();
 		//pilha.pop();
 	}
 	
 	//Save the cost to get to each vertex from initial------------------------------------
 	int dijsize = 0;
 	std::string vertexString;
  for (int j= 0; j<nVertices; j++){
    if(!(parents[j]<-2)){
        vertexString+= std::to_string(j+1)+" "+std::to_string(cost[j])+" "+ +"\n";
        dijsize++;
    }
  }

  std::ofstream outFile;
  outFile.open(output);
  outFile<<dijsize<<"\n"<<vertexString<<"\b "<<std::endl;
  outFile.close();
  //-------------------------------------------------------------------------------------

	//deletes auxiliary arrays
  delete [] parents; delete [] levels; delete [] cost;

}


template class Graph<adjList>;

template class Graph<adjMatrix>;
