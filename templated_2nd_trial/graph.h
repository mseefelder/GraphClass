//#ifndef GRAPH_H
//#define GRAPH_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <limits>
#include <omp.h>
//#include <priority_queue>

#include "adjlist.h"
#include "adjmatrix.h"
#include "heap.h"

class CompareDist //used in the heaps
{
public:
    bool operator()(std::pair<int,int> n1, std::pair<int,int> n2)
    {

      return n1.second<n2.second;

    }
};

/**
 * \class Graph
 *
 * @brief The Graph class
 */
template<class T>
class Graph
{


  public:
    /**
     * @brief Graph Default constructor
     */
    Graph(){
      weighted = false;
      negativeWeight = false;
      nVertices = 0;
    }

    Graph(std::string path,std::string output){
      nVertices = 0;
      weighted = false;
      negativeWeight = false;
      buildGraph(path, output);
    }

    void buildGraph(std::string path,std::string output);

    void BFS(int initial, std::string output);
    void BFS_mod(int initial,float* distance,int* parents);

    //PRIORITY:***
    void Dijkstra(int initial, std::string output);
    void Dijkstra_mod(int initial,float* distance, int* parents);

    //PRIORITY:***
    /*
    We have to choose: *Prim* or Kuskal
    */
    void MST(int initial, std::string output);

    //PRIORITY:**
    /*
    If graph is weighted: use Dijkstra
    Else: use BFS
    */
    void Distance(int vertexA, int vertexB);

    int simpleDistance(int Vertex, float* cost);

    //PRIORITY:**
    void DistanceToAll(int vertex);

    //PRIORITY:**
    float MeanDistance(int init, int end);

    //PRIORITY:*
    void DFS(int initial, std::string output);

    //PRIORITY:*
    int connectedComponents(std::string path);

    //PRIORITY:*
    int getNumberOfVertices();

    //PRIORITY:*
    int Diameter(int b, int e);

    ~Graph(){}

  protected:

  private:

  bool weighted;//if graph is weigthed = true; else = false
  bool negativeWeight;//if graph has a negative weighted edge, can't use Dijkstra
  int nVertices;
  T graph;

};

//#endif // GRAPH_H
