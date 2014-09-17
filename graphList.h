#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include "graph.h"
#include "linkedlist.h"


/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphList: public Graph
{

	public:
    /**
     * @brief Graph Default constructor
     */
    GraphList() {
        graph = NULL;
    }
    
    //int logGraphInfo(string path = "./graphInfo.txt");

	int loadGraph(std::string path,std::string output);// = "./graphInfo.txt");

    int BFS(int inicial, string path) {return 1;}

    //int DFS(int inicial, string path = "./graphBFS.txt");

    //int connectedComponents();

    ~GraphList() {
        if (graph) delete [] graph;
    }

protected:



private:
    /**
     * @brief graphMatrix Data structure if the user chooses Matrix Mode
     */
    linkedList* graph;

};

#endif // GRAPH_H
