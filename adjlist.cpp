#include "adjlist.h"

void adjList::generate(int numVertices){
  data = new std::forward_list< std::pair<int, double> >[numVertices];
  nVertices = numVertices;
  return;
}

void adjList::push(int x, int y, double w){
  data[x].emplace_front(y,w);
  data[y].emplace_front(x,w);
  return;
}

/*
Well, this is just a crazy idea, but check it...

After filling the graph, as it will remain static in our library, we:
convert it into an array of int arrays (faster access);
store the degree for each vertex (to use when looping though all neighbours);
delete the original forward_list array.

Possible optimization: Parallellism in the loop.
*/
void adjList::postProcess(){
  degrees = new int[nVertices];
  vArray = new int*[nVertices]; //first, neigbours; then, weight.
  wArray = new double*[nVertices];

  int size = 0;
  for(int i = 0; i<nVertices; i++){
  	//std::cout<<"Now: "<< i<<std::endl;
    size = 0;

    for ( auto it = data[i].begin(); it != data[i].end(); ++it ){
      size++;
    }

    degrees[i] = size;
    vArray[i] = new int[size];
    wArray[i] = new double[size];

    int index = 0;
    for ( auto it = data[i].begin(); it != data[i].end(); ++it ){
      vArray[i][index] = (*it).first; //std::cout<<" i: "<< (*it).first;
      wArray[i][index] = (*it).second; //std::cout<<" w: "<< (*it).second;
      index++;
    }
    //std::cout<<std::endl;

  }

  delete [] data;

}
