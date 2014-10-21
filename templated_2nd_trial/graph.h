#ifndef GRAPH_H
#define GRAPH_H

#include "adjlist.h"

/**
 * \class Graph
 *
 * @brief The Graph class
 */
template<type T>
class Graph
{
  public:
    /**
     * @brief Graph Default constructor
     */
    Graph(){
      graph = 0;
    }

    Graph(std::string path,std::string output){
      graph = 0;
      buildGraph(path, output);
    }

    ~Graph(){}

    virtual void buildGraph(std::string path,std::string output);

protected:

private:

  bool weighted;//if graph is weigthed = true; else = false

  type graph;

};

#endif // GRAPH_H
