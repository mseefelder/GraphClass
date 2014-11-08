#include <iostream>
#include "graph.h"
#include <sys/time.h>
#include <stdio.h>

int main(){

  std::string open = "especifique_o_caminho";
  std::string out = "analise.txt";

  Graph<adjList> grafo(open,out);

  return 0;
}