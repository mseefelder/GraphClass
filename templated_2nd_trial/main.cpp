#include "graph.h"

int main(){

  std::string open = "grafoteste.txt";
  std::string out = "saindabolada.txt";

  Graph<adjMatrix>* grafo;
  grafo =  new Graph<adjMatrix>;
  grafo->buildGraph(open,out);

  return 0;
}
