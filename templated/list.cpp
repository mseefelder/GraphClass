#include "list.h"

int Glist::maxDegree(){
  for (int j = 0; j<nVertices; j++){
    degrees[vertDegree[j]]++;
    if(vertDegree[j]>maximumDegree) maximumDegree = vertDegree[j];
  }
  return maximumDegree;
}

float Glist::meanDegree(){

  return degreeSum/nVertices;

}

void Glist::pushString(std::string* line){
  std::sscanf(line->c_str(), "%d %d", &x, &y);
  x--; y--;
  data[x].push_front(y);
  data[y].push_front(x);
  mEdges++;
  vertDegree[x]++;
  vertDegree[y]++;
  degreeSum+=2.0;
}

void Glist::empiricalDistribution(std::string* target){
  float temp = 0.0;
  for (int j= 0; j<maximumDegree; j++){
    temp = ((float)degrees[j]/nVertices);
    *target+="Degree:"+std::to_string(j)+" --> "+std::to_string(temp)+"\n";
  }
}
