#include "adjlist.h"

void adjList::generate(int numVertices){
  data = new std::forward_list< std::pair<int, int> >[numVertices];
  nVertices = numVertices;
  return;
}

void adjList::push(int x, int y, int w){
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
  dataArray = new int* [nVertices*2]; //first, neigbours; then, weight.

  int size = 0;
  for(int i = 0; i<nVertices; i++){

    std::cout<<i<<std::endl;

    for ( auto it = data[i].begin(); it != data[i].end(); ++it ){
      size++;
    }

    degrees[i] = size;
    dataArray[i*2] = new int[size];
    dataArray[(i*2)+1] = new int[size];

    int index = 0;
    for ( auto it = data[i].begin(); it != data[i].end(); ++it ){
      dataArray[i*2][index] = (*it).first;
      std::cout<<dataArray[i*2][index];
      dataArray[(i*2)+1][index] = (*it).second;
      std::cout<<" "<<dataArray[(i*2)+1][index]<<std::endl;
      index++;
    }

  }

  delete [] data;

}
