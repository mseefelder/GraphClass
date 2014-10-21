#include "adjlist.h"

void adjList::generate(int numVertices){
  data = new std::forward_list< std::pair<int, int> > data[numVertices];
  return;
}

void adjList::push(int x, int y, int w){
  data[x]->emplace_front(y,w);
  data[y]->emplace_front(x,w);
  return;
}
