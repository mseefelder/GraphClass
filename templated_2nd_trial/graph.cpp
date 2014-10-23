#include "graph.h"

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
  int x,y,weight;
  //Procedure to fill a weighted Graph
  //std::ifstream file;
  file.open(path, std::ifstream::in);
  std::getline (file,line);

  if(weighted){
    //std::sscanf(line.c_str(), "%d %d %d", &x, &y, &weight);
    //graph.push(x,y,weight);
    std::getline(file,line);
    while (!file.eof()){
      std::sscanf(line.c_str(), "%d %d %d", &x, &y, &weight);
      //Correct vertex indexes
      x--; y--;
      //test all the edges for a value < 0
      if(weight<0) negativeWeight = true;
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
      graph.push(x,y,1);
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
  std::cout<<"---BFS---"<<std::endl;
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
      std::cout<<current<<std::endl;
      iterations = graph.degree(current);
      neig = graph.getNeighbours(current);
      for ( int i = 0; i < iterations; i++ ){
        if (parents[*(neig+i)]==-2){
          fifo.push(*(neig+i));
          parents[*(neig+i)]=current;
          levels[*(neig+i)]=levels[current]+1;
        }
      }
      fifo.pop();
  }

  /*
  for(int i  = 0; i<nVertices; i++){
    std::cout<<i;
    neig = graph.getNeighbours(i);
    iterations = graph.degree(i);
    for (int j = 0; j<iterations; j++) std::cout<<" "<<*(neig+j)<<",";
    std::cout<<"\b "<<std::endl;
  }
  */
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

template class Graph<adjList>;

//template class Graph<adjMatrix>;
