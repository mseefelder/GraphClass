#ifndef GRAPHMATRIXRB_H
#define GRAPHMATRIXRB_H

#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include "graph.h"



/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphMatrixRB: public Graph{
	
	public:
    /**
     * @brief Graph Default constructor
     */
    GraphMatrixRB() {
        bitMatrix = NULL;
		nVertices = 0;
    }
    
    //virtual int logGraphInfo(std::string path);// = "./graphInfo.txt");

	virtual int loadGraph(std::string path, std::string output);// = OUTPATH);

    virtual int BFS(int inicial, std::string path);// = "./graphBFS.txt");

    virtual int DFS(int inicial, std::string path);// = "./graphBFS.txt");

    virtual int connectedComponents();

    ~GraphMatrixRB() {
        if (bitMatrix) delete bitMatrix;
     }

protected:



private:
    /**
     * @brief graphMatrix Data structure if the user chooses Matrix Mode
     */
	std::vector<bool>* bitMatrix;
	int nVertices;

};

#endif // GRAPH_H