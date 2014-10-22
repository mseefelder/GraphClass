#include "graph.h"

template<class T> void Graph<T>::buildGraph(std::string path,std::string output){

  std::string line;
  float d_medio; //(sum of all degrees)/number of vertices()

  int mEdges = 0;
  d_medio = 0.0;
  char * value = NULL;

  std::ifstream file;
  file.open(path, std::ifstream::in);
  std::getline (file,line);
  std::sscanf(line.c_str(), "%d", &nVertices);

  //Check whether matrix is weighted or not-------------------------
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


  //Instantiate------------------------------------------------------
  //if(graph) delete graph;
  //graph = new type graph;//WE HAVE TO IMPLEMENT THIS ON THE DATA STRUCTURE
  graph.generate(nVertices);//WE HAVE TO IMPLEMENT THIS

  //Auxiliary structures--------------------------------------------
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

  //Begin graph filling:
  int x,y,weight;
  if(weighted){
    std::sscanf(line.c_str(), "%d %d %d", &x, &y, &weight);
    graph.push(x,y,weight);//WE HAVE TO IMPLEMENT THIS ON THE DATA STRUCTURE


    std::getline(file,line);
    while (!file.eof()){
      std::sscanf(line.c_str(), "%d %d %d", &x, &y, &weight);
      x--; y--;
      graph.push(x,y,weight);
      mEdges++;
      vertDegree[x]++;
      vertDegree[y]++;
      d_medio+=2.0;
      std::getline(file,line);
    }
  }
  else{
    std::sscanf(line.c_str(), "%d %d", &x, &y);
    graph.push(x,y,1);//WE HAVE TO IMPLEMENT THIS ON THE DATA STRUCTURE


    std::getline(file,line);
    while (!file.eof()){
      std::sscanf(line.c_str(), "%d %d", &x, &y);
      x--; y--;
      graph.push(x,y,1);
      mEdges++;
      vertDegree[x]++;
      vertDegree[y]++;
      d_medio+=2.0;
      std::getline(file,line);
    }
  }
  file.close();

  //Graph analysis:--------------------------------------------------------------
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

  return;

}

template class Graph<adjList>;

template class Graph<adjMatrix>;
