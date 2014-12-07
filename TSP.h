#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

//#include <unistd.h>

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

//Traveling Salesman Problem class
class TSP{

public:

	//Loads problem on an array of cities. Just this.
	void open(std::string path){

		std::ifstream file;
		file.open(path,std::ifstream::in);
		file>>nCities; //number of cities in the problem

		cities = new City*[nCities]; //array with all the cities

		//auxiliary variables to create the cities
		double x = 0;
		double y = 0;
		int cityIndex = 0;
		while(true){
			file>>x;
			if (file.eof()) break;
			file>>y;

			cities[cityIndex] = new City(x, y, cityIndex);
			cityIndex++;
		}

		return;
	}

	//Gets city nearest to 0,0 and sets is as starting point
	void setStartingCity(){

		double minimum = 9999999999;//Very big number
		int startingIndex = 0;

		double dist = 0;
		City zeroCity (0,0,-1);

		for (int i = 0; i < nCities; ++i)
		{
			dist = distanceFromCorner(cities[i]);
			cities[i]->cornerDist = dist;
			cities[i]->calcDist = true;
			if (dist<minimum)
			{
				startingIndex = i;
				minimum = dist;
			}
		}

		starter = startingIndex;

		return;
	}

	//Dumbest way to solve, just link cities in the order they were read from the problem
	void solveLinear(){
		std::cout<<"Solving linear: starter = "<<starter<<std::endl;
		//starts at starter, pointing to adjacent city in 'cities'
		int curIndex = starter;
		int nextIndex = (cities[starter]->index)+1;

		while (true){
			cities[curIndex]->nextStop = cities[nextIndex];
			//Prepare for next iteration
			curIndex = nextIndex;
			//Take care not to cross array boundaries
			if (nextIndex+1<nCities) nextIndex = nextIndex+1;
			else nextIndex = 0;
			//If we're back to the start, we're done
			if (nextIndex == starter){
				std::cout<<"Last link: "<<curIndex<<"->"<<starter<<std::endl;
				cities[curIndex]->nextStop = cities[starter];
				break;
			}
		}

		curIndex = starter;
		//Fill solution array:
		solution = new int[nCities];
		for (int i = 0; i < nCities; ++i)
		{
			solution[i] = cities[curIndex]->index;
			cities[curIndex]->indexOnSolution = i;
			curIndex = cities[curIndex]->nextStop->index;
		}
		for (int i = 0 ;i < nCities;i++){

		}

		solved = true;
		return;
	}

	//Each vertex has an edge associated with it. We have N=nCities edges.
	//If we check for each edge if it crosses another edge, we have N**2 checks. (reasonable)
	void twoOpt(){
		std::cout<<"2-Opt. \n Starter: "<<starter<<std::endl;
		double totalDistance = solutionDistance();
		int i, j;
		double aux = 0.0;

		//repeat:
		//i = 0;
		//j = 0;
		for (i = 0; i < nCities; ++i)
		{
			for (j = 0; j < nCities; ++j)
			{	
				//std::cout<<"Pontos: "<<i<<", "<<j<<std::endl;
				//std::cout<<"s: "<<cities[i]->indexOnSolution<<" s:"<<cities[j]->indexOnSolution<<std::endl;
				
				if(i==j || i==starter || j==starter) 
				{
					//std::cout<<"Nao pode ser"<<std::endl;
					continue;
				}

				if(cities[i]->nextStop->index == cities[j]->index) 
				{
					//std::cout<<"Adjacentes!"<<std::endl;
					continue;
				}
				if(cities[j]->nextStop->index == cities[i]->index)
				{
					//std::cout<<"Adjacentes!"<<std::endl;
					continue;
				}

				//std::cout<<"Passou do if"<<std::endl;
				if (pathsCross(cities[i],cities[j]))
				{
					//std::cout << cities[i]->index <<" intersects with "<<cities[j]->index<<"\n";
					//std::cout <<"S:"<<cities[i]->indexOnSolution <<" intersects with "<<"S:"<<cities[j]->indexOnSolution<<"\n";
					
					aux = totalDistance
					- (edgeLength(cities[i]) + edgeLength(cities[j]))
					+ (distance(cities[i], cities[j]) + distance(cities[j]->nextStop,cities[i]->nextStop));

					//std::cout<<aux<<" vs. "<<totalDistance<<std::endl;

					if(totalDistance > aux){
						twoOptSwap(cities[i],cities[j]);
						totalDistance = aux;
						//std::cout<<"Swapped"<<std::endl;
						i = 0; j = 0;
					}
				}
			}
			//std::cout<<"--------------------"<<std::endl;
		}


		return;
	}

	void saveResult(std::string path){
		std::cout<<"1"<<std::endl;
		std::ofstream outFile;
  		outFile.open(path);
  		std::cout<<"2"<<std::endl;
  		outFile<<solutionDistance()<<"\n";
  		std::cout<<"3"<<std::endl;
  		for (int i = 0; i < nCities; ++i)
  		{
  			outFile<<"("<<cities[solution[i]]->pos[0]<<",";
  			outFile<<cities[solution[i]]->pos[1]<<") \n";
  		}
  		std::cout<<"4"<<std::endl;
  		//outFile<<"Final: ("<<cities[solution[nCities]]->nextStop->pos[0]<<",";
  		//outFile<<cities[solution[nCities]]->nextStop->pos[1]<<") \n";
		std::cout<<"5"<<std::endl;
		for (int i = 0; i < nCities; ++i)
		{
			outFile<<cities[i]->index<<"->"<<cities[i]->nextStop->index<<"; ";
		}
		std::cout<<"6"<<std::endl;
		outFile<<"\n";
		for (int i = 0; i < nCities; ++i)
		{
			outFile<<cities[solution[i]]->index<<"->"<<cities[solution[i]]->nextStop->index<<"; ";
		}
		std::cout<<"7"<<std::endl;

  		outFile<<std::endl;
  		outFile.close();
	}

	//Constructor
	TSP(){
		nCities = 0;
		starter = 0;
		cities = NULL;
		solution = NULL;
		solved = false;
	}

	TSP(std::string path){
		nCities = 0;
		starter = 0;
		cities = NULL;
		solution = NULL;
		solved = false;

		open(path);
	}

private:
	//Variables:
	int nCities;
	int starter;
	City** cities;
	int* solution;
	bool solved;

	//Functions:

	//Get city's distance from 0,0
	double distanceFromCorner(City* cityA){

		return sqrt((cityA->pos[0]*cityA->pos[0])+(cityA->pos[1]*cityA->pos[1]));
	}

	//compute distance from one city to another
	double distance(City* cityA, City* cityB){
		return sqrt( ( (cityA->pos[0]-cityB->pos[0]) * (cityA->pos[0]-cityB->pos[0]) ) + ( (cityA->pos[1]-cityB->pos[1]) * (cityA->pos[1]-cityB->pos[1]) ) );
	}

	double edgeLength(City* cityA){
		return sqrt( ( (cityA->pos[0]-cityA->nextStop->pos[0]) * (cityA->pos[0]-cityA->nextStop->pos[0]) )+( (cityA->pos[1]-cityA->nextStop->pos[1]) * (cityA->pos[1]-cityA->nextStop->pos[1]) ) );
	}

	double solutionDistance(){
		double totalDistance = 0.0;
		for (int i = 0; i < nCities; ++i)
		{
			totalDistance += edgeLength(cities[solution[i]]);
			//std::cout<<edgeLength(cities[solution[i]])<<std::endl;
		}
		return totalDistance;
	}

	//Check if two pths between two pairs of cities cross each other
	// http://ideone.com/PnPJgb
	//PROBLEM MUST BE SOLVED
	inline bool onSegment(City* a,City* b,City* nextA){
		if (b->pos[0]<= std::max(a->pos[0],nextA->pos[0]) && b->pos[0]>= std::min(a->pos[0],nextA->pos[0]) &&
				b->pos[1] <= std::max(a->pos[1],nextA->pos[1]) && b->pos[1]>= std::min(a->pos[1],nextA->pos[1]) )
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

	bool doIntersect(City *a, City *b){
		int o1 = orientation(a, a->nextStop, b);
		int o2 = orientation(a, a->nextStop, b->nextStop);
		int o3 = orientation(b, b->nextStop , a);
		int o4 = orientation(b, b->nextStop ,a->nextStop);

		if (o1 != o2 && o3 != o4) return true;

		if (o1 == 0 && onSegment(a, b, a->nextStop)) return true;
		if (o2 == 0 && onSegment(a, b->nextStop,a->nextStop)) return true;
		if (o3 == 0 && onSegment(b, a, b->nextStop)) return true;
		if (o4 == 0 && onSegment(b, a->nextStop , b->nextStop)) return true;

		return false;
	}

	bool pathsCross(City* cityA, City* cityB){

		double CmPxr = ( cityB->pos[0] - cityA->pos[0]) * ( cityA->nextStop->pos[1] - cityA->pos[1]) - ( cityB->pos[1] - cityA->pos[1]) * ( cityA->nextStop->pos[0] - cityA->pos[0]);
		double CmPxs = ( cityB->pos[0] - cityA->pos[0]) * ( cityB->nextStop->pos[1] - cityB->pos[1]) - ( cityB->pos[1] - cityA->pos[1]) * ( cityB->nextStop->pos[0] - cityB->pos[0]);
		double rxs = ( cityA->nextStop->pos[0] - cityA->pos[0]) * ( cityB->nextStop->pos[1] - cityB->pos[1]) - ( cityA->nextStop->pos[1] - cityA->pos[1]) * ( cityB->nextStop->pos[0] - cityB->pos[0]);

		if ( CmPxr == 0)
		{
		// Lines are collinear, and so intersect if they have any overlap

		return ( ( cityB->pos[0] - cityA->pos[0] < 0) != ( cityB->pos[0] - cityA->nextStop->pos[0] < 0))
		|| ( ( cityB->pos[1] - cityA->pos[1] < 0) != ( cityB->pos[1] - cityA->nextStop->pos[1] < 0));
		}

		if ( rxs == 0)
		return false; // Lines are parallel.

		double rxsr = 1 / rxs;
		double t = CmPxs * rxsr;
		double u = CmPxr * rxsr;

		return (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1);
	}

	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//ONLY CALLED BY twoOpt(): swapping operation when paths cross
	void twoOptSwap(City* cityA, City* cityB){
		//Here I have to do the path swap on the nodes and on the solution array!
		//std::cout<<"Swapping edges..."<<std::endl;
		int aux = cityA->nextStop->indexOnSolution;
		int end = cityB->nextStop->indexOnSolution;

		//On the nodes:
		City* temp = cityA->nextStop;
		cityA->nextStop = cityB;
		temp->nextStop = cityB->nextStop;

		int curIndex = cityB->indexOnSolution;
		while(true){
			//std::cout<<curIndex<<std::endl;
			cities[solution[curIndex]]->nextStop = cities[solution[curIndex-1]];
			if(curIndex = temp->indexOnSolution || curIndex == 1) break;
			curIndex--;
		}

		/*
		std::cout<<"Before swap: \n    Aux: S:"<<aux<<" End: S:"<<end<<std::endl;
		if(!(aux > nCities || end < 0)){
			while(true){
				std::cout<<"!";
				swapSolutionArray(aux,end);
				aux++;
				end--;
				if(aux == end || end==aux+1 || aux > nCities || end < 0) break;
			}
		}
		*/
		curIndex = starter;
		//Fill solution array:
		for (int i = 0; i < nCities; ++i)
		{
			solution[i] = cities[curIndex]->index;
			cities[curIndex]->indexOnSolution = i;
			curIndex = cities[curIndex]->nextStop->index;
		}
	}

	void swapSolutionArray(int a, int b){
		std::cout<<"Swapping array..."<<std::endl;
		if (a == b) return;
		//std::cout<<cities[solution[a]]->index<<"<-->"<<cities[solution[a]]->index<<std::endl;
		int temp = solution[a];
		solution[a] = solution[b];
		solution[b] = temp;
		return;
	}


};

/*

TO DO:

*/
