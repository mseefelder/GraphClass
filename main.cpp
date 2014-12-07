#include <iostream>
#include "graph.h"
#include <sys/time.h>
#include <stdio.h>

int main(){

  std::string open = "../dblp.txt";
  std::string out = "analise.txt";

  Graph<adjList> grafo(open,out);

  return 0;
}
