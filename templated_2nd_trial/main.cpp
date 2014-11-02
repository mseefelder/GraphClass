#include <iostream>
#include "graph.h"
#include <sys/time.h>
#include <stdio.h>

int main(){

  std::string open = "../../datasets/graph3.txt";
  std::string open1 = "../../datasets/rede_colaboracao.txt";
  std::string open2 = "K4.txt";
  std::string out = "saidabolada2.txt";
  std::string out2 = "saidabolada3.txt";

  /*
  bool repeat = true;
  while(repeat){

    std::cout<<"Caminho para o grafo: "<<std::endl;
    std::cin>>open;
    std::cout<<"Caminho para salvar análise: "<<std::endl;
    std::cin>>out;
    std::cout<<"Caminho para salvar MST: "<<std::endl;
    std::cin>>out2;
    std::string youn = " ";

    Graph<adjList> grafo(open,out);
    grafo.Distance(1,10);
    grafo.Distance(1,20);
    grafo.Distance(1,30);
    grafo.Distance(1,40);
    grafo.Distance(1,50);
    double ti,tf,tempo; // ti = tempo inicial // tf = tempo final
    ti = tf = tempo = 0;
    timeval tempo_inicio,tempo_fim;
    gettimeofday(&tempo_inicio,NULL);
    grafo.MST(1,out2);
    gettimeofday(&tempo_fim,NULL);
    tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
    ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
    tempo = (tf - ti) / 1000;
    printf("Tempo gasto em milissegundos %.3f\n",tempo);
    std::cout<<"Quer recomecar? (y ou n)"<<std::endl;
    std::cin>>youn;
    if(youn == "y") repeat = true;
    else if(youn == "n") repeat = false;
    else repeat = false;
  }
  */

  Graph<adjList> grafo(open,out);

  int final = grafo.getNumberOfVertices();
  std::cout<<grafo.MeanDistance(1, final)<<std::endl;

  //std::cout<<grafo.getNumberOfVertices()<<std::endl;
  //grafo.Diameter(0,grafo.getNumberOfVertices());
  //grafo.connectedComponents(out2);
  //std::cout<< "fim BFS" << std::endl;
  //grafo.Distance(1,3621);
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