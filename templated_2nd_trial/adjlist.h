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

    std::forward_list< std::pair<int, double> >* data;
    int** vArray;
    double** wArray;
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

    void push(int x, int y, double w);

    int degree(int v) const {return degrees[v];}

    bool getNeighbours(int vertex, int** array) const {
      *array = vArray[vertex];
      return false;
    }

    bool getWeights(int vertex, double** array) const {
      //std::cout<<"In list: getWeights:: ";
      //for (int i = 0; i<degrees[vertex]; i++) std::cout<<"w "<<wArray[vertex][i]<<" ";
      //std::cout<<std::endl;
      *array = wArray[vertex];
      return false;
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
