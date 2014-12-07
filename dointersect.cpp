#include <iostream>
using namespace std;

struct City{

  double pos[2]; // x= pos[0], y= pos[1]
  double cornerDist;
  int index;
  int indexOnSolution;
  bool beenTo, left, calcDist;
  City* nextStop;

  City(){
    pos[0] = 0;
    pos[1] = 0;
    index = 0;
    beenTo = false;
    left = false;
    nextStop = NULL;
    cornerDist = 0.0;
    calcDist = false;
  }
  City(double x, double y, int i){
    pos[0] = x;
    pos[1] = y;
    index = i;
    beenTo = false;
    left = false;
    nextStop = NULL;
    cornerDist = 0.0;
    calcDist = false;
  }
};
inline bool onSegment(City* a,City* b,City* nextA){
  if (b->pos[0]<= max(a->pos[0],nextA->pos[0]) && b->pos[0]>= min(a->pos[0],nextA->pos[0]) &&
      b->pos[1] <= max(a->pos[1],nextA->pos[1]) && b->pos[1]>= min(a->pos[1],nextA->pos[1]) )
      {
        return true;
      }
  return false;
}
inline int orientation(City *a, City *b , City *nextA){
  int val  = (b->pos[1] - a->pos[1]) * (nextA->pos[0] - b->pos[0])-
             (b->pos[0] - a->pos[0]) * (nextA->pos[1] - b->pos[1]);
  if(val ==0)  return 0;
  return (val > 0)? 1: 2;
}

bool doIntersect(City *a, City *nextA, City *b, City *nextB){
    int o1 = orientation(a, nextA, b);
    int o2 = orientation(a, nextA, nextB);
    int o3 = orientation(b, nextB , a);
    int o4 = orientation(b, nextB ,nextA);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(a, b, nextA)) return true;
    if (o2 == 0 && onSegment(a, nextB,nextA)) return true;
    if (o3 == 0 && onSegment(b, a, nextB)) return true;
    if (o4 == 0 && onSegment(b, nextA, nextB)) return true;

    return false;
}
int main(){
  City a(914061,22681,0);
  City nextA(721054,802978,1);
  City b(936293,266919,2);
  City nextB(383510,678241,3);
  doIntersect(&a, &nextA, &b, &nextB)? cout << "Yes\n": cout << "No\n";
  a.pos[0] = 10;
  a.pos[1] = 0;
  nextA.pos[0] = 0;
  nextA.pos[1] = 10;
  b.pos[0] = 0;
  b.pos[1] = 0;
  nextB.pos[0] = 10;
  nextB.pos[1] = 10;
  doIntersect(&a, &nextA, &b, &nextB)? cout << "Yes\n": cout << "No\n";

}
