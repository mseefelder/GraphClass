#ifndef GRAPHMATRIXA_H
#define GRAPHMATRIXA_H

#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <queue>
#include "graph.h"


/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphMatrixA: public Graph{
	
	public:
    /**
     * @brief Graph Default constructor
     */
    GraphMatrixA() {
        bitMatrix = NULL;
		nVertices = 0;
    }
    
    //virtual int logGraphInfo(std::string path);// = "./graphInfo.txt");

	virtual int loadGraph(std::string path, std::string output);// = OUTPATH);

    virtual int BFS(int inicial, std::string path);// = "./graphBFS.txt");

    //int DFS(int inicial, std::string path);// = "./graphBFS.txt");

    //int connectedComponents();

    ~GraphMatrixA() {
        if (bitMatrix) delete bitMatrix;
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
