#include "graph.h"

template<class T> void Graph<T>::buildGraph(std::string path,std::string output){

  //Line used to parse the graph file
  std::string line;
  //(sum of all degrees)/number of vertices()
  double mean_degree = 0.0;
  //number of edges on the graph
  int mEdges = 0;

  std::cout<<"ahuahuahua"<<std::endl;
  //Open graph file:------------------------------------------------------------
  std::ifstream file;
  //file.open(path, std::ifstream::in);
  file.open(path);
  std::getline (file,line);
  std::sscanf(line.c_str(), "%d", &nVertices);
  std::cout<<"ahuahuahua"<<std::endl;
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
  //stores for each vertex: it's degree
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
  double weight;
  //Procedure to fill a weighted Graph
  //std::ifstream file;
  file.open(path, std::ifstream::in);
  std::getline (file,line);//discard nVertices line

  if(weighted){    
    //std::getline(file,line);
    while (true){//!file.eof()){
      //std::sscanf(line.c_str(), "%d %d %f", &x, &y, &weight);
      //alternative:----------
      file>>x;
      if(file.eof()) break;
      file>>y;
      file>>weight;
      //----------------------
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
      //std::getline(file,line);
    }
  }

  //Procedure to fill a non-weighted Graph
  else{
    //std::sscanf(line.c_str(), "%d %d", &x, &y);
    //graph.push(x,y,1);//WE HAVE TO IMPLEMENT THIS ON THE DATA STRUCTURE
    //std::getline(file,line);
    while (true){//} (!file.eof()){
      //std::sscanf(line.c_str(), "%d %d", &x, &y);
      //alternative:----------
      file>>x;
      if(file.eof()) break;
      file>>y;
      //----------------------
      x--; y--;
      //std::cout<<"   "<<x<<","<<y<<std::endl;
      graph.push(x,y,1.0);
      mEdges++;
      vertDegree[x]++;
      vertDegree[y]++;
      mean_degree+=2.0;
      //std::getline(file,line);
    }
  }
  //Finished reading graph, close file:
  file.close();
  std::cout<<"ahuahuahua"<<std::endl;
  //Graph analysis:-------------------------------------------------------------

  //Find 3 maximum degrees:
  // int maxVert1 = 0; int maxVert2 = 1; int maxVert3 = 2;
  // int maxDegree1 = vertDegree[0]; int maxDegree2 = vertDegree[1]; int maxDegree3 = vertDegree[2];
  // for (int j = 3; j<nVertices; j++){
  //   if(maxDegree1<maxDegree2 && maxDegree1<maxDegree3){
  //     if(vertDegree[j]>maxDegree1){
  //       maxVert1 = j;
  //       maxDegree1 = vertDegree[j];
  //     }
  //   }
  //   else if(maxDegree2<maxDegree1 && maxDegree2<maxDegree3){
  //     if(vertDegree[j]>maxDegree2){
  //       maxVert2 = j;
  //       maxDegree2 = vertDegree[j];
  //     }
  //   }
  //   else if(maxDegree3<maxDegree2 && maxDegree3<maxDegree1){
  //     if(vertDegree[j]>maxDegree3){
  //       maxVert3 = j;
  //       maxDegree3 = vertDegree[j];
  //     }
  //   }
  // }
 
  
  int maxDegree1 = 0;
  int maxIndex1 = 0;
  for (int j = 0; j<nVertices; j++){
    if(vertDegree[j]>maxDegree1){ 
      maxDegree1 = vertDegree[j];
      maxIndex1 = j;
    }
  }

  int maxDegree2 = 0;
  int maxIndex2 = 0;
  for (int j = 0; j<nVertices; j++){
    if(j!=maxIndex1){
      if(vertDegree[j]>maxDegree2){ 
        maxDegree2 = vertDegree[j];
        maxIndex2 = j;
      }
    }
  }

  int maxDegree3 = 0;
  int maxIndex3 = 0;
  for (int j = 0; j<nVertices; j++){
    if(j!=maxIndex1 && j!=maxIndex2){
      if(vertDegree[j]>maxDegree3){ 
        maxDegree3 = vertDegree[j];
        maxIndex3 = j;
      }
    }
  }

  std::cout<<"MaxVert1: "<<maxIndex1<<" Degree: "<<maxDegree1<<std::endl;
  std::cout<<"MaxVert2: "<<maxIndex2<<" Degree: "<<maxDegree2<<std::endl;
  std::cout<<"MaxVert3: "<<maxIndex3<<" Degree: "<<maxDegree3<<std::endl;

  int maxDegree = 0;
  for (int j = 0; j<nVertices; j++){
    degrees[vertDegree[j]]++;
    if(vertDegree[j]>maxDegree) maxDegree = vertDegree[j];
  }
  

  //Prepare a string with empirical distribution of degrees
  std::string degreeString;
  double temp = 0.0;
  for (int j= 0; j<maxDegree; j++){
    temp = ((double)degrees[j]/nVertices);
    degreeString+="Degree:"+std::to_string(j)+" --> "+std::to_string(temp)+"\n";
  }

  //Compute mean degree
  mean_degree = mean_degree/nVertices;

  //Write file with graph analysis
  std::ofstream outFile;
  outFile.open(output);
  outFile<<"Max Degree:"<<maxDegree<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#mean_degree = "<<mean_degree<<"\n"<<degreeString<<std::endl;

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
 	double* cost;
 	cost = new double[nVertices];

 	int starter = 999999999;//very big double (gambiarra)
 	heap<double> pilha(nVertices,starter);

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
 	double* weig = NULL; //array to store weights
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
        vertexString+= std::to_string(j+1)+" "+std::to_string(cost[j])+" "+std::to_string(parents[j]) +"\n";
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

  double* distance;
  distance = new double[nVertices];

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

template<class T> int Graph<T>::simpleDistance(int Vertex, double* cost) const{
  int* parents;
  parents = new int[nVertices];
  int numberOfPairs = 0; //Vertex; //nVertices-Vertex;

  //Weighted case---------------------------------------------------
  if (weighted == true && negativeWeight == false){
    Dijkstra_mod(Vertex,cost,parents);
  }
  //Non-weighted case-------------------------------------------------
  else if(weighted == false){
    BFS_mod(Vertex,cost,parents);
  }

  /*
  #pragma omp critical
  {
  /////------------------------------------------------------------------
  std::cout<<"[";
  for (int i = 0; i < nVertices; ++i)
  {
   std::cout<<cost[i]<<", ";
  }
  std::cout<<"\b ]";
  for (int i = 0; i < nVertices; ++i)
  {
   std::cout<<parents[i]<<", ";
  }
  std::cout<<"\b ]";
  */

  //for (int i = Vertex; i < nVertices; ++i)
  for (int i = 0; i < Vertex; ++i)
  {
    //if(parents[i] < 0) numberOfPairs--;
    if(parents[i] != -2) if(parents[i] != -1)numberOfPairs++;
  }

  /*
  std::cout<<" numberOfPairs: "<<numberOfPairs<<std::endl;
  /////------------------------------------------------------------------
  }
  */

  delete [] parents;

  return numberOfPairs;
}

template<class T> void Graph<T>::BFS_mod(int initial,double* distance, int* parents) const{
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

template<class T> void Graph<T>::Dijkstra_mod(int initial,double* distance,int* parents) const{

  //Correct inicial index
  initial--;

  double starter = DBL_MAX;//-5000;//std::numeric_limits<double>::infinity();//very big double (gambiarra)
  //std::cout<<"starter"<<starter<<std::endl;
  heap<double> pilha(nVertices,starter);

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
  double* weig = NULL; //array to store weights
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
        if(currentValue==starter){}
        else if(weig[i]==starter){}
        else if(pilha.cost(neig[i])==starter){
          //std::cout<<"Parents"<<std::endl;
          parents[neig[i]] = current;
          //std::cout<<"Distance"<<std::endl;
          distance[neig[i]] = (currentValue + weig[i]);
          pilha.replace( neig[i], (currentValue + weig[i]) );
          ////#pragma omp critical
          ////std::cout<<"Replace: "<<neig[i]<<", "<<(currentValue)<<std::endl;
        }
        else if(pilha.cost(neig[i])>(currentValue + weig[i]) ){
        	//std::cout<<"Parents"<<std::endl;
          parents[neig[i]] = current;
          //std::cout<<"Distance"<<std::endl;
          distance[neig[i]] = (currentValue + weig[i]);
          pilha.replace( neig[i], (currentValue + weig[i]) );
          ////#pragma omp critical
          ////std::cout<<"Replace: "<<neig[i]<<", "<<(currentValue)<<std::endl;
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
 	double* cost;
 	cost = new double[nVertices];

 	int starter = 999999999;//very big double (gambiarra)
 	heap<double> pilha(nVertices,starter);

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
 	double* weig = NULL; //array to store weights
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

  /*
  int* feig = NULL;
  iterations = graph.degree(2272);
  deleteFlagN = graph.getNeighbours(2272,&feig);
  std::string neigString;
  for(int i = 0 ; i<iterations;i++){
    if(parents[feig[i]] == 2272){
    neigString += std::to_string(feig[i]) + ", ";
    }
  }
  std::cout << neigString << std:: endl;

  if(deleteFlagN){
    delete [] feig;
  }
  */
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
  double total_cost = 0;
  for ( int w = 0; w<nVertices;w++){
    if(parents[w]>-1){
      total_cost += cost[w];
    }
  }
  std::cout<<total_cost<<std::endl;
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
  outFile<<dijsize<<"\n"<<total_cost<<"\n"<<vertexString<<"\b "<<std::endl;
  outFile.close();
  //-------------------------------------------------------------------------------------
  
	//deletes auxiliary arrays
  delete [] parents; delete [] levels; delete [] cost;

}

template<class T> void Graph<T>::conservativeMST(int initial, std::string output){
  //Correct inicial index
  initial--;

  //Store each element's parent
  int* parents;
  parents = new int[nVertices];

  //Store each element's level
  int* levels;
  levels = new int[nVertices];

  //Store each element's cost
  double* cost;
  cost = new double[nVertices];

  int starter = 999999999;//very big double (gambiarra)
  heap<double> pilha(nVertices,starter);

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
  double* weig = NULL; //array to store weights
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

  /*
  int* feig = NULL;
  iterations = graph.degree(2272);
  deleteFlagN = graph.getNeighbours(2272,&feig);
  std::string neigString;
  for(int i = 0 ; i<iterations;i++){
    if(parents[feig[i]] == 2272){
    neigString += std::to_string(feig[i]) + ", ";
    }
  }
  std::cout << neigString << std:: endl;

  if(deleteFlagN){
    delete [] feig;
  }
  */
  //Save the cost to get to each vertex from initial------------------------------------
  int dijsize = nVertices;
  std::string vertexString;
  for (int j= 0; j<nVertices; j++){
    if(parents[j]==-1){}
    else if(!(parents[j]<-1)){
        vertexString+=std::to_string(parents[j]+1)+" "+std::to_string(j+1)+"\n";//+" "+std::to_string(cost[j])+"\n";
    }
    else{dijsize--;}
  }

  std::ofstream outFile;
  outFile.open(output);
  outFile<<nVertices<<"\n"<<vertexString;
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
    double* distance;
    distance = new double[nVertices];
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
    double* distance;
    distance = new double[nVertices];
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

template<class T> double Graph<T>::MeanDistance(int init, int end) const{

  int threadN = omp_get_max_threads();
  //Store the distance sum on each thread
  double distance[threadN];
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
    double cost[nVertices];

    for (int k = 0; k < nVertices; ++k)
    {
      cost[k] = 0;
    }

    //-----------------------------------------------
    #pragma omp for
      for (int i = init; i < end+1; ++i)
      {
        usedPairs[thread] += simpleDistance( i , cost);
        //sum all values on cost[] (erasing them) and add to distance[thread]
        for (int j = 0; j < nVertices; ++j)
        { 
            if((j+1)<i && cost[j]>-1){
            distance[thread]+=cost[j];

            //if(cost[j]==-1) {
            //  distance[thread]++;
            //}
          }
          cost[j]=0;
        }
      }
    //-----------------------------------------------

  }
  //-----------------------------------------------//-----------------------------------------------

  double mean = 0.0;
  //int totalThreads = 0;
  double totalSum = 0.0;

  double totalPairs = 0.0;
  //long long totalPairsLong = 0;
  for (int i = 0; i < threadN; ++i)
  {
    totalPairs += (double)usedPairs[i];
    //totalPairsLong += usedPairs[i];
  }

  double* threadWeight; threadWeight = new double[threadN];
  for (int i = 0; i < threadN; ++i)
  {
    threadWeight[i] = 0.0;
  }
  double totalWeight = 0.0;

  std::cout<<"Distance | Used Pairs | Weight \n";

  //Calculate mean:
  for (int t = 0; t < threadN; ++t)
  {
    if(usedPairs[t]>0){
      std::cout<<"["<<t<<"] ";
      std::cout<<distance[t]<<" | "<<usedPairs[t];
      totalSum += distance[t];
      //totalThreads += 1;

      threadWeight[t] = ((double)usedPairs[t]/totalPairs);
      totalWeight += threadWeight[t];

      std::cout<<" | "<<threadWeight[t]<<"\n";

      mean += threadWeight[t]*(distance[t]/usedPairs[t]);
    }
  }

  std::cout<<"Total weight: "<<totalWeight<<std::endl;
  std::cout<<"Total sum: "<<totalSum<<std::endl;
  std::cout<<"Total of used pairs: "<<totalPairs<<std::endl;

  mean = mean/totalWeight;
  std::cout<<"Mean Distance: "<<mean<<std::endl;

  return mean;

}

template<class T> void Graph<T>::DFS(int initial, std::string output){
	//Correcting index
  initial = initial -1;

  //Auxiliary queue used during the algorithm
  std::stack<int> lifo;
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
  lifo.push(initial);

  int current = 0;
  int* neig = NULL;
  int elementIndex=0;
  int iterations = 0;
  bool deleteFlag;
  while(!lifo.empty()){
      current = lifo.top();
			lifo.pop();
      iterations = graph.degree(current);
      deleteFlag = graph.getNeighbours(current, &neig);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[neig[i]]==-2){
          lifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          levels[*(neig+i)]=levels[current]+1;
        }
      }
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
template<class T> int Graph<T>::connectedComponents(std::string path){
  std::cout<<">>||"<<std::endl;
  int nComponents = 0 ;//vai contar o número de componentes

  //para armazenar pares de <elemento por onde comecei a bfs, tamanho da componente conexa>
  std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >,CompareDist > myHeap;

  bool* vertices;
  vertices = new bool[nVertices];//vai marcar quem já ta em alguma CC
  std::queue<int> fifo;
  int size = 0;

  for(int x = 0;x<nVertices;x++){
    vertices[x] = false;//pra primeira BFS, começa tudo falso
  }
  int current = 0;
  int* neig = NULL;
  int iterations = 0;
  bool deleteFlagN;
  std::cout<<"1BFS"<<std::endl;

  for(int i = 0;i<nVertices;i++){
    size = 0;
    if(vertices[i]==false){
      fifo.push(i);
      vertices[i] = true;
      size++;
      nComponents++;
      while(!fifo.empty()){
        current = fifo.front(); //fifo.pop() <--removes the object and returns void
        iterations = graph.degree(current);
        deleteFlagN = graph.getNeighbours(current, &neig);
        for (int j = 0;j<iterations;j++){
          if (vertices[neig[j]]==false){//nessa primeira BFS só olha os vertices que ainda estão false
            fifo.push(*(neig+j));
            vertices[*(neig+j)] = true;
            size++;
          }
        }
      fifo.pop();
      if(deleteFlagN){
        delete [] neig;
        }
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
    ccOrder[i] = new int[size+1];//aloca tamanho size+1 pra colocar no elemento 0 qual o tamanho da componente que ta vindo e depois insere os vertices todos
    vertice = myHeap.top().first;
    ccOrder[i][0] = size;//temos q colocar isso no arquivo e usar pra otimizar o loop de output
    ccOrder[i][1] = vertice+1;//bota o elemento que vai começar a BFS
    myHeap.pop();

    //rodo a BFS a partir do vertice e aloco na array da componente conexa dele
    fifo.push(vertice);
    vertices[vertice] = false;
    while(!fifo.empty()){
      current = fifo.front();
      iterations = graph.degree(current);
      deleteFlagN = graph.getNeighbours(current, &neig);
      for (int j = 0;j<iterations;j++){
        if (vertices[neig[j]]==true){
          fifo.push(*(neig+j));
          vertices[*(neig+j)] = false;
          counter++;
          ccOrder[i][counter] = neig[j]+1;
        }
      }
      fifo.pop();
      if(deleteFlagN){
        delete [] neig;
      }
    }
  }
  std::cout<<"2BFS5"<<std::endl;
  std::cout<<"2BFS-end"<<std::endl;

  //printo
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

template<class T> int Graph<T>::getNumberOfVertices(){
  return nVertices;
}

template<class T> int Graph<T>::Diameter(int b, int e){
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
 bool deleteFlagN;
 int* neig = NULL;

 std::cout<<"Setup done!"<<std::endl;

#pragma omp parallel
{
//////////////A partir daqui tem uma cópia em cada thread, rodando
  int thread = omp_get_thread_num();
  int current = 0;
  bool deleteFlagN;
  int* neig = NULL;
  int localDiameter = 0;
  int iterations = 0;

 //Primeira BFS, pega pra cada componente o vertice inicial e o tamanho
#pragma omp for
////////--------------------------------------Esse for e dividido entre os threads
 for(int i = begin;i<end;i++){

     for(int x = 0; x<nVertices; x++){levels[thread][x] = -1;}
     fifo[thread].push(i);
     levels[thread][i] = 0;
     localDiameter = -1;

     while(!fifo[thread].empty()){
       current = fifo[thread].front(); //fifo.pop() <--removes the object and returns void
       iterations = graph.degree(current);
       deleteFlagN = graph.getNeighbours(current, &neig);
       for (int j= 0;j<iterations;j++){

         if (levels[thread][neig[j]]==-1){

           fifo[thread].push(*(neig+j));
           levels[thread][*(neig+j)]=levels[thread][current]+1;
           if(levels[thread][*(neig+j)]>localDiameter) localDiameter = levels[thread][*(neig+j)];

         }

       }

     fifo[thread].pop();

     }
     if(localDiameter>diameters[thread]) diameters[thread] = localDiameter;
////////--------------------------------------
  }

//////////////
 for(int j = 0; j<threadN; j++){
   if(diameters[j]>diameter) diameter = diameters[j];
 }
 }
 std::cout<<"\n ---"<<diameter<<"---\n"<<std::endl;
 delete [] levels;
 delete [] diameters;
 return diameter;

}



template class Graph<adjList>;

template class Graph<adjMatrix>;
