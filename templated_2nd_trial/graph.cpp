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
  //std::cout << "lendo"<< std::endl;
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
  //std::cout << "weighted : "<< weighted << std::endl;

  file.close();

  //Instantiate-----------------------------------------------------------------

  graph.generate(nVertices);//WE HAVE TO IMPLEMENT THIS
  //std::cout << "generate"<< std::endl;
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
  //std::cout << "starting postProcess"<< std::endl;
  graph.postProcess();//
  //std::cout << "fim"<< std::endl;
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
  bool deleteFlag;
  while(!fifo.empty()){
      current = fifo.front();
      iterations = graph.degree(current);
      deleteFlag = graph.getNeighbours(current, &neig);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[neig[i]]==-2){
          fifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          levels[*(neig+i)]=levels[current]+1;
        }
      }
      fifo.pop();
      if(deleteFlag){
        delete [] neig;
      }
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
  int curCost;
 	int iterations; //for each vertex, a different # of iterations
 	int* neig = NULL; //array to store neighbours
 	float* weig = NULL; //array to store weights
  bool deleteFlagN;
  bool deleteFlagW;
 	while(!pilha.empty()){
 		//std::cout<<std::endl;
 		//pilha.printTable();//Logs the weights in each element
 		//pilha.printHeap();
 		current = pilha.top_index();//Gets the minimum value element
    curCost = pilha.cost(current);
 		iterations = graph.degree(current);
 		deleteFlagN = graph.getNeighbours(current,&neig);
 		deleteFlagW = graph.getWeights(current,&weig);

    pilha.pop();

 		for(int i =0;i < iterations; i++){

 			if(pilha.exists(neig[i])){

 				//std::cout<<"index:"<<neig[i]<<"; cost:"<<pilha.cost(neig[i]);
 				//std::cout<<"; current:"<<pilha.cost(current)<<"; weight:"<<weig[i];
 				//std::cout<<std::endl;

 				if(pilha.cost(neig[i])>(curCost + weig[i]) ){
 					parents[neig[i]] = current;
 					levels[neig[i]] = levels[current] + 1;
 					cost[neig[i]] = (curCost + weig[i]);

 					//std::cout<<"   "<<neig[i]<<","<<pilha.cost(current) + weig[i]<<std::endl;

 					pilha.replace( neig[i], (curCost + weig[i]) );
 				}

 			}

 		}
    if(deleteFlagN){
      delete [] neig;}
    if(deleteFlagW){
      delete [] weig;}
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

  float* distance;
  distance = new float[nVertices];

  //Weighted case---------------------------------------------------
  if (weighted == true && negativeWeight == false){
    Dijkstra_mod(VertexA,distance,parents);

	}
	//Non-weighted case-------------------------------------------------
  else if(weighted == false){
    BFS_mod(VertexA,distance,parents);
  }

  int counter;
  counter = VertexB - 1;//VertexB - 1 to correct index!::::::

  //In case VertexA doesn't reach VertexB:
  if(parents[VertexB-1]<0){
    std::cout<<"Nao ha caminho de "<<VertexA<<" para "<<VertexB<<"!"<<std::endl;
    return;
  }

  else{
    std::cout<<"Distancia : "<<distance[VertexB-1]<< " ";
    counter = VertexB - 1;
    while(counter != (VertexA - 1) ){// != (VertexA - 1), what we look for!:::::
      //path +=std::to_string(counter+1)+ ", ";
      std::cout<< counter+1 << ", ";
      counter = parents[counter];
    }
    std::cout<<VertexA<< std::endl;
  }

  delete [] distance;
  delete [] parents;

  return;
}

template<class T> int Graph<T>::simpleDistance(int Vertex, float* cost){
  int* parents;
  parents = new int[nVertices];

  //Weighted case---------------------------------------------------
  if (weighted == true && negativeWeight == false){
    Dijkstra_mod(Vertex,cost,parents);
  }
  //Non-weighted case-------------------------------------------------
  else if(weighted == false){
    BFS_mod(Vertex,cost,parents);
  }

  int numberOfPairs = nVertices-Vertex;
  for (int i = Vertex; i < nVertices; ++i)
  {
    if(parents[i] == -1) numberOfPairs--;
  }

  delete [] parents;

  return numberOfPairs;
}

template<class T> void Graph<T>::BFS_mod(int initial,float* distance, int* parents){
  //Correcting index
  initial = initial -1;

  //Auxiliary queue used during the algorithm
  std::queue<int> fifo;
  //For each vertex: store its parent
  //For each vertex: store its level
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
  int iterations = 0;
  bool deleteFlag;
  while(!fifo.empty()){
      current = fifo.front();
      iterations = graph.degree(current);
      deleteFlag = graph.getNeighbours(current, &neig);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[neig[i]]==-2){
          fifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          distance[*(neig+i)] = distance[current]+1;
        }
      }
      fifo.pop();
      if(deleteFlag){
        delete [] neig;
      }
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
  int currentValue;
  int iterations; //for each vertex, a different # of iterations
  int* neig = NULL; //array to store neighbours
  float* weig = NULL; //array to store weights
  bool deleteFlagN;
  bool deleteFlagW;
  while(!pilha.empty()){
 		current = pilha.top_index();//Gets the minimum value element
 		currentValue = pilha.cost(current);
 		//std::cout<<"::::Current vertex"<<current<<std::endl;
 		//std::cout<<pilha.cost(current)<<std::endl;
 		iterations = graph.degree(current);
 		deleteFlagN = graph.getNeighbours(current,&neig);
 		deleteFlagW = graph.getWeights(current,&weig);

 		pilha.pop();

    for(int i =0;i < iterations; i++){

    	// std::cout<<"v:"<<current;for(int i=0; i<iterations; i++)std::cout<<" n:"<<neig[i];std::cout<<std::endl;
 		// 	std::cout<<"exists("<<neig[i]<<")"<<std::endl;
      //
 		// 	std::cout<<"index:"<<neig[i]<<"; cost:"<<pilha.cost(neig[i]);
 		// 	std::cout<<"; current:"<<currentValue<<"; weight:"<<weig[i];
 		// 	std::cout<<std::endl;

      if(pilha.exists(neig[i])){
        if(pilha.cost(neig[i])>(currentValue + weig[i]) ){
        	//std::cout<<"Parents"<<std::endl;
          parents[neig[i]] = current;
          //std::cout<<"Distance"<<std::endl;
          distance[neig[i]] = (currentValue + weig[i]);
          pilha.replace( neig[i], (currentValue + weig[i]) );
        }
      }
    }
    if(deleteFlagN){
      delete [] neig;
    }
    if(deleteFlagW){
      delete [] weig;
    }
  }
  //std::cout<<"Dijkstra_mod finished!::::::::::::::::::::";
  //for(int i=0;i<nVertices;i++)std::cout<<"distance["<<i<<"] ="<<distance[i]<<" ";
  //std::cout<<std::endl;
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
  bool deleteFlagN;
  bool deleteFlagW;
 	while(!pilha.empty()){
 		//std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------- \n";
 		//std::cout<<std::endl;
 		//pilha.printTable();//Logs the weights in each element
 		//pilha.printHeap();
 		current = pilha.top_index();//Gets the minimum value element
 		iterations = graph.degree(current);
 		deleteFlagN = graph.getNeighbours(current,&neig);
 		deleteFlagW = graph.getWeights(current,&weig);

 		pilha.pop();

 		for(int i =0;i < iterations; i++){
 			//std::cout<<"v:"<<current;for(int i=0; i<iterations; i++)std::cout<<" n:"<<neig[i];std::cout<<std::endl;
 			//std::cout<<"exists("<<neig[i]<<")"<<std::endl;
 			if(pilha.exists(neig[i])){

 				//std::cout<<"index:"<<neig[i]<<"; cost:"<<pilha.cost(neig[i]);
 				//std::cout<<"; current:"<<pilha.cost(current)<<"; weight:"<<weig[i];
 				//std::cout<<std::endl;

 				if(pilha.cost(neig[i]) > weig[i] ){
 					parents[neig[i]] = current;
 					levels[neig[i]] = levels[current] + 1;
 					cost[neig[i]] = weig[i];

 					//std::cout<<"   >Replace ["<<neig[i]<<"] ,"<<weig[i]<<std::endl;

 					pilha.replace( neig[i], weig[i] );
 				}

 			}

 		}
    if(deleteFlagN){
      delete [] neig;
    }
    if(deleteFlagW){
      delete [] weig;
    }
 	}

 	//Save the cost to get to each vertex from initial------------------------------------
  int* newindex;
  newindex = new int[nVertices];
  int removed = 0;
  for (int j= 0; j<nVertices; j++){
    if(!(parents[j]<-1)){
      newindex[j] = (j+1)- removed;
    }
    else{
      newindex[j]= -1;
      removed++;
      }
  }
 	int dijsize = nVertices;
 	std::string vertexString;
  for (int j= 0; j<nVertices; j++){
    if(parents[j]==-1){}
    else if(!(parents[j]<-1)){
        vertexString+=std::to_string(newindex[parents[j]])+" "+std::to_string(newindex[j])+" "+std::to_string(cost[j])+" "+ +"\n";
    }
    else{dijsize--;}
  }

  std::ofstream outFile;
  outFile.open(output);
  outFile<<dijsize<<"\n"<<vertexString<<"\b "<<std::endl;
  outFile.close();
  //-------------------------------------------------------------------------------------

	//deletes auxiliary arrays
  delete [] parents; delete [] levels; delete [] cost;

}

template<class T> void Graph<T>::DistanceToAll(int Vertex){
  int* parents;
  parents = new int[nVertices];
  std::string path;

  //Weighted case---------------------------------------------------
  if (weighted == true && negativeWeight == false){
    float* distance;
    distance = new float[nVertices];
    Dijkstra_mod(Vertex,distance,parents);
    int counter;
    for(int i= 1 ;i<(nVertices + 1);i++){
      if(i != Vertex-1){

        if(parents[i-1]<0){
        }
        else{
          std::cout<<"vertice : "<<i<<" distancia : "<<distance[i-1]<< " ";
          counter = i - 1;
          while(counter != (Vertex - 1) ){// != (VertexA - 1), what we look for!:::::
            //path +=std::to_string(counter+1)+ ", ";
            std::cout<< counter+1 << ", ";
            counter = parents[counter];
          }
          std::cout<<Vertex<< std::endl;
          //path += std::to_string(Vertex);

          //std::cout<<"Distancia : " << distance[i-1] <<" "<< "Caminho : " << path << std::endl;
          //path = "";
        }
      }
    }
    delete [] distance;
  }
  //Non-weighted case-------------------------------------------------
  else if(weighted == false){
    float* distance;
    distance = new float[nVertices];
    BFS_mod(Vertex,distance,parents);
    int counter;
    for(int i= 1 ;i<(nVertices + 1);i++){
      if(i != Vertex-1){
        if(parents[i-1]<0){
        }
        else{

          std::cout<<"vertice : "<<i<<" distancia : "<<distance[i-1]<< " ";
          counter = i - 1;
          while(counter != (Vertex - 1) ){// != (VertexA - 1), what we look for!:::::
            //path +=std::to_string(counter+1)+ ", ";
            std::cout<< counter+1 << ", ";
            counter = parents[counter];
          }
          std::cout<<Vertex<< std::endl;
          //path += std::to_string(Vertex);

          //std::cout<<"Distancia : " << distance[i-1] <<" "<< "Caminho : " << path << std::endl;
          //path = "";
        }
      }
    }
    delete [] distance;
  }
  delete [] parents;
  return;
}

template<class T> float Graph<T>::MeanDistance(){
  
  int threadN = omp_get_max_threads();
  //Store the distance sum on each thread
  float distance[threadN];
  //Store the # of considered pair on each thread
  int usedPairs[threadN];

  for (int i = 0; i < threadN; ++i)
  {
    distance[i] = 0.0;
    usedPairs[i] = 0;
  }

  #pragma omp parallel
  //-----------------------------------------------//-----------------------------------------------
  {
    int thread = omp_get_thread_num();
    float cost[nVertices];

    for (int k = 0; k < nVertices; ++k)
    {
      cost[k] = 0;
    }

    //-----------------------------------------------
    #pragma omp for
      for (int i = 0; i < nVertices; ++i)
      {
        usedPairs[thread] += simpleDistance( (i+1) , cost);
        //sum all values on cost[] (erasing them) and add to distance[thread]
        for (int j = i+1; j < nVertices; ++j)
        {
          distance[thread]+=cost[j];
          
          if(cost[j]==-1) {
            distance[thread]++;
          }
          cost[j]=0;
        }
      }  
    //-----------------------------------------------

  }
  //-----------------------------------------------//-----------------------------------------------
  
  float mean = 0.0;
  int totalThreads = 0.0;
  //Calculate mean:
  for (int t = 0; t < threadN; ++t)
  {
    if(usedPairs[t]>0){
      mean += (distance[t]/usedPairs[t]);
      totalThreads += 1.0;
    }
  }
  mean = mean/totalThreads;

  return mean;

}

template class Graph<adjList>;

template class Graph<adjMatrix>;
