#ifndef GRAPH_H
#define GRAPH_H

#include <string>

/**
 * \class Graph
 *
 * @brief The Graph class
 */
class Graph
{

    /**
     * @brief Graph Default constructor
     */
    Graph() {
        graphMatrix = NULL;
        graphList = NULL;
    }

    /**
     * @brief logGraphInfo Logs info about the graph to a text file.
     *
     * The text file format is:
     * # n = number of vertices
     * # m = number of edges
     * # d_medio = mean degree
     * 1 f(1) = n(1)/n
     * 2 f(2) = n(2)/n
     * ...
     * d f(d)
     *
     * @param path Where to save the log
     * @return 1 if successfull, -1 if not
     */
    int logGraphInfo(string path = "./graphInfo.txt");

    /**
     * @brief BFS Runs a Breadth-first search and saves the result to a text file
     *
     * The text output contains:
     * The search tree.
     * The root's degree is zero.
     * To represent the tree just list for each vertex:
     *  it's parent
     *  it's degree
     *
     * @param inicial Vertex from wich the search starts
     * @param path Where to save the results
     * @return 1 if successfull, -1 if not
     */
    int BFS(int inicial, string path = "./graphBFS.txt");

    /**
     * @brief DFS Runs a Depth-first search and saves the result to a text file
     *
     * The text output contains:
     * The search tree.
     * The root's degree is zero.
     * To represent the tree just list for each vertex:
     *  it's parent
     *  it's degree
     *
     * @param inicial Vertex from wich the search starts
     * @param path Where to save the results
     * @return 1 if successfull, -1 if not
     */
    int DFS(int inicial, string path = "./graphBFS.txt");

    /**
     * @brief connectedComponents Computes the graph's Connected Components on a text file.
     *
     * Text output format:
     * The number of connected components
     * Size of each component
     * Lists of vertices belonging to each component (in decrescent order of component size)
     *
     * @return 1 if successfull, -1 if not
     */
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
    int * graphMatrix;

    /**
     * @brief graphList Data structure if the user chooses List Mode
     */
    int ** graphList;
};

#endif // GRAPH_H
