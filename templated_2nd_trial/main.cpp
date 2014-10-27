#include <iostream>
#include "graph.h"

int main(){

  std::string open = "example.txt";
  std::string out = "saidabolada2.txt";
  std::string out2 = "saidabolada3.txt";

  Graph<adjList> grafo(open,out);
  grafo.Distance(1,2);
  grafo.MST(1,out);


/*
  int size = 5;
  heap<int> pilha(size,999999);
  for (int i = 0; i<size; i++) std::cout<<pilha.peek(i)<<std::endl;
  std::cout<<"------- \n";
  for (int i = 0; i<size; i++) std::cout<<pilha.vpeek(i)<<std::endl;
  std::cout<<"------- \n";
  for (int i = 0; i<size; i++) std::cout<<pilha.getValueIndex(i)<<std::endl;
  std::cout<<"------- \n";
  //pilha.swap(2,0);
  //pilha.getValueIndex(0);
  pilha.replace(2,0);
  pilha.replace(4,8);
  pilha.replace(3,3);
  pilha.replace(1,5);
  std::cout<<"------- \n";
  for (int i = 0; i<size; i++) std::cout<<pilha.peek(i)<<std::endl;
  std::cout<<"------- \n";
  for (int i = 0; i<size; i++) std::cout<<pilha.vpeek(i)<<std::endl;
  std::cout<<"------- \n";
  for (int i = 0; i<size; i++) std::cout<<pilha.getValueIndex(i)<<std::endl;
  std::cout<<"------- \n";
*/

  return 0;
}
