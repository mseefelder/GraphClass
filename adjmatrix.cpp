#include "adjmatrix.h"

void adjMatrix::generate(int numVertices){
	long long size = (numVertices*(numVertices-1))/2;
  data = new double[size];
  for(int i = 0; i<size; i++){
  	data[i] = -1.0;
  }

	nVertices = numVertices;

 	return;
}

void adjMatrix::push(int x, int y, double w){
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

void adjMatrix::postProcess(){
	degrees = new int[nVertices];

	int size = 0;

	long long index;
	for(int x = 0; x<nVertices; x++){
		size = 0;
		for(int y = 0; y<nVertices; y++){
			if(x != y){
				if (x > y){
					index = (((x+1)*x)/2)-x+y;
					if(data[index]>0.0) {
						size++;
					}
				}
				else{
					index = (((y+1)*y)/2)-y+x;
					if(data[index]>0.0){
						size++;
					}
				}
			}
		}
		degrees[x]=size;
	}
	return;
}
