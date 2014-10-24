#include <iostream>
#include "heap.h"

int main(){
/*
  std::string open = "grafoteste.txt";
  std::string out = "saidabolada2.txt";

  Graph<adjList> grafo(open,out);
  grafo.MST(1,out);
*/
  int size = 3;
  heap<int> pilha(size,1);
  for (int i = 0; i<size; i++) std::cout<<pilha.peek(i)<<std::endl;
  for (int i = 0; i<size; i++) std::cout<<pilha.vpeek(i)<<std::endl;
  pilha.update(2,0);
  for (int i = 0; i<size; i++) std::cout<<pilha.peek(i)<<std::endl;
  for (int i = 0; i<size; i++) std::cout<<pilha.vpeek(i)<<std::endl;
  return 0;
}
