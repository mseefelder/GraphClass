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

    long* data;

  public:
    /**
     * @brief Graph Default constructor
     */
    adjMatrix(){
      data = NULL;
    }

    void generate(int numVertices);

    void push(int x, int y, int w);

    ~adjMatrix(){
	if (data) delete [] data;
}

protected:



};

#endif // ADJLIST_H

