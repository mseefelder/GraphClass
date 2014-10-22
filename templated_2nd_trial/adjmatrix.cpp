#include "adjmatrix.h"

void adjMatrix::generate(int numVertices){
     data = new long[(nVertices*(nVertices-1))/2];
  return;
}

void adjMatrix::push(int x, int y, int w){
    x--; y--;
    if (x > y){data[(((x+1)*x)/2)-x+y] = w;}
    else{data[(((y+1)*y)/2)-y+x] = w;}
  return;
}

