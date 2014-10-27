#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <forward_list>

/**
 * \class Matrix
 *
 * @brief The Graph class
 */
class adjMatrix
{
  private:
    /*
    A int array beacause we have to store weights.
    This array will be indexed ALWAYS with "long long"'s (refer to
     .cpp to see it).
    */
    float* data;
    int* degrees;
    int nVertices;

  public:
    /**
     * @brief Graph Default constructor
     */
    adjMatrix(){
      data = NULL;
      degrees = NULL;
      nVertices = 0;
    }

    void generate(int numVertices);

    void push(int x, int y, float w);

    int degree(int v){return degrees[v];}

    bool getNeighbours(int vertex, int** array){
      int* draft;
      *array = new int[degrees[vertex]];
      draft = *array;

      long long index = 0;
      int counter = 0;
      for(int i = 0; i<nVertices; i++){
        if (vertex > i){
          index = (((vertex+1)*vertex)/2)-vertex+i;
        }
        else{
          index = (((i+1)*i)/2)-i+vertex;
        }
        if(data[index]!=-1){
          draft[counter]=i;
          counter++;
        }
      }
      return true;
    }

    bool getWeights(int vertex, float** array){
      float* draft;
      *array = new float[degrees[vertex]];
      draft = *array;

      long long index = 0;
      int counter = 0;
      for(int i = 0; i<nVertices; i++){
        if (vertex > i){
          index = (((vertex+1)*vertex)/2)-vertex+i;
        }
        else{
          index = (((i+1)*i)/2)-i+vertex;
        }
        if(data[index]!=-1){
          draft[counter]=data[index];
          counter++;
        }
      }
      return true;
    }

    void postProcess();

    ~adjMatrix(){
      if (data) delete [] data;
    }

protected:



};

#endif // ADJLIST_H
