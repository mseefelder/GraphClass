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

    std::forward_list< std::pair<int, int> >* data;
    int** dataArray;
    int nVertices;
    int* degrees;

  public:
    /**
     * @brief Graph Default constructor
     */
    adjList(){
      data = NULL;
      dataArray = NULL;
      degrees = NULL;
      nVertices = 0;
    }

    void generate(int numVertices);

    void postProcess();

    void push(int x, int y, int w);

    int degree(int v){return degrees[v];}

    int* getNeighbours(int vertex){
      return dataArray[vertex*2];
    }

    void getWeights(int vertex, int* array){
      array = dataArray[(vertex*2)+1];
      return;
    }

    ~adjList(){
      if (dataArray){
        for(int i=0; i<nVertices; i++){
          delete [] dataArray[i];
        }
        delete [] dataArray;
      }
      if (degrees){
        delete [] degrees;
      }

    }

protected:



};

#endif // ADJLIST_H
