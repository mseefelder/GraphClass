#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

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
class Graph
{
	public:
    /**
     * @brief Graph Default constructor
     */
    Graph(){}


    /**
     * @brief logGraphInfo Logs info about the graph to a text file.
     *
     * The text file format is: \n
     * '#' n = number of vertices \n
     * '#' m = number of edges \n
     * '#' d_medio = mean degree \n
     * 1 f(1) = n(1)/n \n
     * 2 f(2) = n(2)/n \n
     * ... \n
     * d f(d) \n
     *
     * @param path Where to read graph from
     * @param output Where to save the log
     * @return 1
     */
    //int logGraphInfo(std::string path);// = "./graphInfo.txt");

	virtual int loadGraph(std::string path,std::string output) = 0;// = "./graphInfo.txt");

    /**
     * @brief BFS Runs a Breadth-first search and saves the result to a text file
     *
     * The text output contains: \n
     * The search tree. \n
     * The root's degree is zero. \n
     * To represent the tree just list for each vertex: \n
     *  it's parent \n
     *  it's degree \n
     *
     * @param inicial Vertex from wich the search starts
     * @param path Where to save the results
     * @return 1
     */
    virtual int BFS(int inicial, std::string path) = 0;// = "./graphBFS.txt");

    /**
     * @brief DFS Runs a Depth-first search and saves the result to a text file
     *
     * The text output contains:\n
     * The search tree.\n
     * The root's degree is zero.\n
     * To represent the tree just list for each vertex:\n
     *  it's parent\n
     *  it's degree\n
     *
     * @param inicial Vertex from wich the search starts
     * @param path Where to save the results
     * @return 1
     */
    virtual int DFS(int inicial, std::string path) = 0;

    /**
     * @brief connectedComponents Computes the graph's Connected Components on a text file.
     *
     * Text output format:\n
     * The number of connected components\n
     * Size of each component\n
     * Lists of vertices belonging to each component (in decrescent order of component size)\n
     *
     * @return 1
     */
    virtual int connectedComponents()=0;
    
    virtual int Diameter(int b, int e)=0;

    ~Graph(){}

protected:



private:

};

#endif // GRAPH_H
