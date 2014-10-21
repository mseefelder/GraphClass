#ifndef GRAPHDATABASE_H
#define GRAPHDATABASE_H

#include "list.h"
//#include "matrix.h"

class CompareDist //used in GraphList::Diameter()
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
template <class T>
class GraphDataBase
{
  public:
    /**
     * @brief Graph Default constructor
     */
    GraphDataBase(){}

    GraphDataBase(std::string* path, std::string* output){}

    ~GraphDataBase(){}

protected:

private:

  T* data;
  int nVertices;

};

#endif // GRAPHDATA_H
