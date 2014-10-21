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

  public:
    /**
     * @brief Graph Default constructor
     */
    adjList(){
      data = NULL;
    }

    void generate(int numVertices);

    void push(int x, int y, int w);

    ~adjList(){}

protected:



};

#endif // ADJLIST_H
