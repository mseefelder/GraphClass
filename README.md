GraphClass
==========

A graph class



Base class:
Graph --> graph.h & graph.cpp

Classes working:
GraphMatrixA --> graphM.h & graphM.cpp
	to compile an example with it:
	g++ -std=c++11 -Wall -o example  graph.cpp graphM.cpp main.cpp
GraphMatrixR --> graphMred.h & graphMred.cpp (reduced matrix owing to Gaussian Sum wizardry)
	to compile an example with it:
	g++ -std=c++11 -Wall -o example  graph.cpp graphMred.cpp main_reduced.cpp
linkedList --> linkedlist.h

Classes broken:
GraphList --> graphList.h & graphist.cpp (has to be implemented!)
GraphMatrix --> graphMatrix.h & graphMatrix.cpp

To Do list:
Matrix:
[x]Data structure
[x]LOG
[x]BFS
[]DFS
[]Connected Components

List:
[not working]Data structure
[]LOG
[]BFS
[]DFS
[]Connected Components

