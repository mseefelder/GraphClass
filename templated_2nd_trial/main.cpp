#include "graph.h"

int main(){

  std::string open = "grafoteste.txt";
  std::string out = "saindabolada.txt";

  Graph<adjList>* grafo;
  grafo =  new Graph<adjList>;
  grafo->buildGraph(open,out);

  return 0;
}
