#include "adjmatrix.h"

void adjMatrix::generate(int numVertices){
	std::cout<<"!"<<std::endl;
	int size = (numVertices*(numVertices-1))/2;

	std::cout<<"!"<<std::endl;
    data = new int[size];
 	
 	std::cout<<"!"<<std::endl;
    for(int i = 0; i<size; i++){
    	data[i] = 0;
    }

    std::cout<<"!"<<std::endl;
 	return;
}

void adjMatrix::push(int x, int y, int w){

	std::cout<<"!"<<std::endl;
    x--; y--;
    int index;
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

