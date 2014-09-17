#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <fstream>
#include <iostream>
#include <cstdlib>
using std::string;
#include <string>
#include <forward_list>//http://www.cplusplus.com/reference/forward_list/forward_list/
#include <queue>
#include <stack>
#include <vector>
#include "graph.h"
#include "linkedlist.h"


/**
 * \class Graph
 *
 * @brief The Graph class
 */
class GraphListS: public Graph
{

	public:
    /**
     * @brief Graph Default constructor
     */
    GraphListS() {
        graph = NULL;
        nVertices = 0;
    }
    
    //int logGraphInfo(string path = "./graphInfo.txt");

	virtual int loadGraph(std::string path,std::string output);// = "./graphInfo.txt");

    virtual int BFS(int inicial, std::string path);

    virtual int DFS(int inicial, std::string path);// = "./graphBFS.txt");

    virtual int connectedComponents();

    ~GraphListS() {
        if (graph) delete [] graph;
    }

protected:



private:
    /**
     * @brief graphMatrix Data structure if the user chooses Matrix Mode
     */
    std::forward_list<int>* graph;
    int nVertices;

};

#endif // GRAPH_H
