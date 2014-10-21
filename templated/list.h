#ifndef GLIST_H
#define GLIST_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <forward_list>

/**
 * \class List
 *
 * @brief The Graph class
 */
class Glist
{
  private:

    std::forward_list<int>* data;
    int nVertices, x, y, mEdges, maximumDegree;
    float degreeSum;
    int* vertDegree;
    int* degrees;
  public:
    /**
     * @brief Graph Default constructor
     */
    Glist(int n){
      nVertices = n;
      x = 0; y = 0; mEdges = 0; degreeSum = 0.0; maximumDegree = 0;

      vertDegree = new int[nVertices];//for each vertex, store it's degree
      for (int i = 0; i<nVertices; i++){
          vertDegree[i]=0;
      }

      degrees = new int[nVertices-1]; //for each degree, indicate # of vertices that has it
      for (int i = 0; i<(nVertices-1); i++){
          degrees[i]=0;
      }

      data = new std::forward_list<int>[nVertices];
    }

    void pushString(std::string* line);

    int maxDegree();

    void empiricalDistribution(std::string* target);

    float meanDegree();

    ~Glist(){}

protected:



};

#endif // GLIST_H
