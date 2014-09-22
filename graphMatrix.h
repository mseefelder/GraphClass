#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <queue>
#include <stack>
#include "graph.h"



/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphMatrix: public Graph{
	
	public:
    /**
     * @brief Graph Default constructor
     */
    GraphMatrix() {
        bitMatrix = NULL;
		nVertices = 0;
    }

	virtual int loadGraph(std::string path, std::string output);

    virtual int BFS(int inicial, std::string path);

    virtual int DFS(int inicial, std::string path);

    virtual int connectedComponents(std::string path);
    
    virtual int Diameter(int b, int e);
    
    virtual int getNumberOfVertices();

    ~GraphMatrix() {
        if (bitMatrix) delete [] bitMatrix;
     }

protected:



private:
    /**
     * @brief graphMatrix Data structure if the user chooses Matrix Mode
     */
	bool* bitMatrix;
	int nVertices;

};

#endif // GRAPH_H
