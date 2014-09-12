#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphMatrix: public Graph
{

    /**
     * @brief Graph Default constructor
     */
    Graph() {
        graph = NULL;
    }
    
    int logGraphInfo(string path = "./graphInfo.txt");

	int loadGraph(string path);

    int BFS(int inicial, string path = "./graphBFS.txt");

    int DFS(int inicial, string path = "./graphBFS.txt");

    int connectedComponents();

    ~Graph() {
        if (graphMatrix) delete graphMatrix;
        if (graphList) delete graphList;
    }

protected:



private:
    /**
     * @brief graphMatrix Data structure if the user chooses Matrix Mode
     */
    bool ** graph;

};

#endif // GRAPH_H
