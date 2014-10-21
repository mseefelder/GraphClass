#ifndef GRAPH_H
#define GRAPH_H

#include "graphdata.h"

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
    Graph(){
    	graph = 0;
    }

    Graph(std::string path,std::string output){
    	graph = 0;
    	buildGraph(path, output);
    }

    ~Graph(){}


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

	virtual int buildGraph(std::string path,std::string output);// = "./graphInfo.txt");

protected:

private:

	bool weighted;
	bool isList;

	GraphData graph;

};

#endif // GRAPH_H
