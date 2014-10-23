#include "graph.h"

int main(){

  std::string open = "grafoteste.txt";
  std::string out = "saidabolada2.txt";

  Graph<adjMatrix> grafo(open,out);
  grafo.BFS(1,out);

  return 0;
}
