#ifndef ADJLIST_H
#define ADJLIST_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <forward_list>

/**
 * \class List
 *
 * @brief The Graph class
 */
class adjList
{
  private:

    std::forward_list< std::pair<int, float> >* data;
    int** vArray;
    float** wArray;
    int nVertices;
    int* degrees;

  public:
    /**
     * @brief Graph Default constructor
     */
    adjList(){
      data = NULL;
      vArray = NULL;
      degrees = NULL;
      nVertices = 0;
    }

    void generate(int numVertices);

    void postProcess();

    void push(int x, int y, float w);

    int degree(int v){return degrees[v];}

    void getNeighbours(int vertex, int** array){
      *array = vArray[vertex];
      return;
    }

    void getWeights(int vertex, float** array){
      //std::cout<<"In list: getWeights:: ";
      //for (int i = 0; i<degrees[vertex]; i++) std::cout<<"w "<<wArray[vertex][i]<<" ";
      //std::cout<<std::endl;
      *array = wArray[vertex];
      return;
    }

    ~adjList(){

      if (vArray){
        for(int i=0; i<nVertices; i++){
          delete [] vArray[i];
        }
        delete [] vArray;
      }


      if (wArray){
        for(int i=0; i<nVertices; i++){
          delete [] wArray[i];
        }
        delete [] wArray;
      }

      if (degrees){
        delete [] degrees;
      }

    }

protected:



};

#endif // ADJLIST_H
