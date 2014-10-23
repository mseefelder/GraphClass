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
    int* data;
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

    void push(int x, int y, int w);

    int degree(int v){return degrees[v];}

    int checkVertex(int vertex, int neighbour){

      return 0;
    }

    int checkWeight(int vertex, int neighbour){
      return 0;
    }

    void postProcess();

    ~adjMatrix(){
      if (data) delete [] data;
    }

protected:



};

#endif // ADJLIST_H
