#include <iostream>
#include "graph.h"
#include <sys/time.h>
#include <stdio.h>

int main(){

  std::string open = "../../datasets/grafo_5.txt";
  std::string open1 = "../../datasets/rede_colaboracao.txt";
  std::string out = "saidabolada2.txt";
  std::string out2 = "saidabolada3.txt";

  Graph<adjList> grafo(open1,out);
  /*double ti,tf,tempo; // ti = tempo inicial // tf = tempo final
  ti = tf = tempo = 0;
  timeval tempo_inicio,tempo_fim;
  gettimeofday(&tempo_inicio,NULL);*/
  grafo.MST(1,out2);
  /*gettimeofday(&tempo_fim,NULL);
  tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
  ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
  tempo = (tf - ti) / 1000;
  printf("Tempo gasto em milissegundos %.3f\n",tempo);*/

  //std::cout<<grafo.getNumberOfVertices()<<std::endl;
  //grafo.Diameter(0,grafo.getNumberOfVertices());
  //grafo.connectedComponents(out2);
  //std::cout<< "fim BFS" << std::endl;
  //grafo.Distance(1,4);
  //grafo.Dijkstra(1,out);
  //grafo.Dijkstra(2,out);
  //grafo.Dijkstra(3,out);
  //grafo.Dijkstra(4,out);
  //grafo.Dijkstra(5,out);
  //grafo.Dijkstra(6,out);
  //grafo.Dijkstra(7,out);
  //std::cout<<"MST::::::::::;"<<std::endl;
  //grafo.MST(1,out2);
  //std::cout<< "fim MST" << std::endl;
  //grafo.MST(7,out);
  //grafo.Distance(3,4);
  //std::cout<<grafo.MeanDistance()<<std::endl;

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
