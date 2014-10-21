#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include "list.h"
//#include "matrix.h"

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
template <class T>
class GraphData
{
	public:
    /**
     * @brief Graph Default constructor
     */
    GraphData(){
      data = 0;
      nVertices = 0;
    }

    GraphData(std::string* path, std::string* output){
      std::string line;
      int x,y,mEdges;
      float d_medio; //(sum of all degrees)/number of vertices()

      mEdges = 0;
      d_medio = 0.0;
      char * value = NULL;

      std::ifstream file;
      file.open(*path, std::ifstream::in);
      std::getline (file,line);
      std::sscanf(line.c_str(), "%d", &nVertices);

      //data = new T(nVertices);
      data = new Glist(nVertices);

      std::getline(file,line);
      while (!file.eof()){
        data->pushString(&line); //create this
        std::getline(file,line);
      }

      file.close();

      int maxDegree = data->maxDegree();//create this

      std::string degreeString;
      data->empiricalDistribution(&degreeString); //create this

      d_medio = data->meanDegree(); //create this to output

      std::ofstream outFile;
      outFile.open(*output);
      outFile<<"#n = "<<nVertices<<"\n"<<"#m = "<<mEdges<<"\n"<<"#d_medio = "<<d_medio<<"\n"<<degreeString<<std::endl;
    }

    ~GraphData(){}

protected:

private:

	T* data;
  int nVertices;

};

#endif // GRAPHDATA_H
