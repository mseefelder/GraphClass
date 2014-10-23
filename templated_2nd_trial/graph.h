//#ifndef GRAPH_H
//#define GRAPH_H

#include <queue>

#include "adjlist.h"
#include "adjmatrix.h"

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

    //PRIORITY:***
    void BFS(int initial, std::string output);

    //PRIORITY:***
    //void Djikstra(int initial, std::string output);

    //PRIORITY:***
    /*
    We have to choose: Prim or Kuskal
    */
    //void MST(std::string output);

    //PRIORITY:**
    /*
    If graph is weighted: use Dijkstra
    Else: use BFS
    */
    //void Distance(int vertexA, int vertexB);

    //PRIORITY:**
    //void DistanceToAll();

    //PRIORITY:**
    //void MeanDistance();

    //PRIORITY:*
    //void DFS(int initial, std::string output);

    //PRIORITY:*
    //int connectedComponents(std::string path);

    //PRIORITY:*
    //int getNumberOfVertices();

    //PRIORITY:*
    //int Diameter(int b, int e);

    ~Graph(){}

  protected:

  private:

  bool weighted;//if graph is weigthed = true; else = false
  bool negativeWeight;//if graph has a negative weighted edge, can't use Dijkstra
  int nVertices;
  T graph;

};

//#endif // GRAPH_H
