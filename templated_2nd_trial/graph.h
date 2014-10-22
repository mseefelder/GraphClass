//#ifndef GRAPH_H
//#define GRAPH_H

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
      nVertices = 0;
    }

    void buildGraph(std::string path,std::string output);

    Graph(std::string path,std::string output){
      nVertices = 0;
      weighted = false;
      buildGraph(path, output);
    }

    ~Graph(){}

  protected:

  private:

  bool weighted;//if graph is weigthed = true; else = false
  int nVertices;
  T graph;

};

//#endif // GRAPH_H
