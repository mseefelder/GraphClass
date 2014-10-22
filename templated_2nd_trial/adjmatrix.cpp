#include "adjmatrix.h"

void adjMatrix::generate(int numVertices){
	long long size = (numVertices*(numVertices-1))/2;
  data = new int[size];
  for(int i = 0; i<size; i++){
  	data[i] = 0;
  }
 	return;
}

void adjMatrix::push(int x, int y, int w){
  x--; y--;
  long long index;
  if (x > y){
  	index = (((x+1)*x)/2)-x+y;
  	data[index] = w;
  }
  else{
  	index = (((y+1)*y)/2)-y+x;
  	data[index] = w;
  }
  return;
}
