#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>

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
	//Not the best idea. Later we may implement checking what is the best vertex to start.
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

	//Solves by finding nearest neighbors, greedy heuristic
	void greedytravel(){
		int nextIndex = -1;
		int passed[nCities];
		std::queue<int> fifo;
		for(int i=0 ; i<nCities; i++){
			passed[i] = 0;
		}
		double mindistance;
		fifo.push(starter);
		int curIndex = 0;
		while(!fifo.empty()){
			curIndex = fifo.front();
			passed[curIndex] = 1;
			double aux = 0.0;
			mindistance = 999999999999;
			for(int i=0 ; i<nCities; i++){
				if (i != curIndex){
					if(passed[i] == 0){
						aux = distance(cities[curIndex],cities[i]);
						if (aux < mindistance) {
							mindistance = aux;
							nextIndex = i;
						}
					}
				}
			}
			if(nextIndex != -1){
				cities[curIndex]->nextStop = cities[nextIndex];
				fifo.push(nextIndex);
				passed[nextIndex] = 1;
			}
			else if(nextIndex == -1){
				cities[curIndex]->nextStop = cities[starter];
			}
			fifo.pop();
			nextIndex = -1;
		}
		std::cout<<"Done linking"<<std::endl;
		curIndex = starter;
		//Fill solution array:
		solution = new int[nCities];
		for (int i = 0; i < nCities; ++i)
		{
			solution[i] = cities[curIndex]->index;
			cities[curIndex]->indexOnSolution = i;
			curIndex = cities[curIndex]->nextStop->index;
		}
		solved = true;
		return;	
	}

	//2-OPT checks all edge pairs until it finds a pair that crosses.
	//It then, checks if uncrossing this pair is better. 
	//If yes it is done and the checking is reset.
	void twoOpt(){
		std::cout<<"2-Opt. \n Starter: "<<starter<<std::endl;
		double totalDistance = solutionDistance();
		int i, j;
		double aux = 0.0;

		for (i = 0; i < nCities; ++i)
		{
			for (j = 0; j < nCities; ++j)
			{	
				
				if(i==j)
				{
					continue;
				}

				if(cities[i]->nextStop->index == cities[j]->index) 
				{
					continue;
				}
				if(cities[j]->nextStop->index == cities[i]->index)
				{
					continue;
				}
				if (pathsCross(cities[i],cities[j]))
				{
					//calculate the path distance if we do the swap
					aux = totalDistance
					- (edgeLength(cities[i]) + edgeLength(cities[j]))
					+ (distance(cities[i], cities[j]) + distance(cities[j]->nextStop,cities[i]->nextStop));

					if(totalDistance > aux){
						twoOptSwap(cities[i],cities[j]);
						totalDistance = aux;
						//reset checking, a change has been made in the solution
						i = 0; j = 0;
					}
					else if(totalDistance < aux) std::cout<<"No swap this time"<<std::endl;
				}
			}
		}
		return;
	}

	//Function to save result to a file
	void saveResult(std::string path){
		std::ofstream outFile;
  		outFile.open(path);
  		outFile<<solutionDistance()<<"\n";
		for (int i = 0; i < nCities; ++i)
		{
			outFile<<(cities[solution[i]]->index)+1<<" ";
		}
  		outFile<<std::endl;
  		outFile.close();
	}

	//Constructors
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
	//number of cities:
	int nCities;
	//city chosen to start solving the problem
	int starter;
	//Array containing all cities
	City** cities;
	//Array containing the solution
	int* solution;
	//Indicates if a solution has been calculated
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

	//A city has a pointer to the next city visited after itself. 
	//We consider this an edge. This function calculates this edge's length.
	double edgeLength(City* cityA){
		return sqrt( ( (cityA->pos[0]-cityA->nextStop->pos[0]) * (cityA->pos[0]-cityA->nextStop->pos[0]) )+( (cityA->pos[1]-cityA->nextStop->pos[1]) * (cityA->pos[1]-cityA->nextStop->pos[1]) ) );
	}

	//Distance if we go through all the solution
	double solutionDistance(){
		double totalDistance = 0.0;
		for (int i = 0; i < nCities; ++i)
		{
			totalDistance += edgeLength(cities[solution[i]]);
		}
		return totalDistance;
	}

	//Check if two pths between two pairs of cities cross each other
	//Adapted from http://ideone.com/PnPJgb
	//PROBLEM MUST BE SOLVED TO USE THIS FUNCTION
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

	//ONLY CALLED BY twoOpt(): swapping operation when paths cross
	void twoOptSwap(City* cityA, City* cityB){
		//Here I have to do the path swap on the nodes and on the solution array!
		int curIndex = 0;

		if(cityA->indexOnSolution <= cityB->indexOnSolution){
			int aux = cityA->nextStop->indexOnSolution;
			int end = cityB->nextStop->indexOnSolution;

			//On the nodes:
			City* temp = cityA->nextStop;
			cityA->nextStop = cityB;
			temp->nextStop = cityB->nextStop;

			curIndex = cityB->indexOnSolution;
			while(true){
				if(curIndex == temp->indexOnSolution) break;
				cities[solution[curIndex]]->nextStop = cities[solution[curIndex-1]];
				if(curIndex == 0) curIndex = nCities-1;
				else curIndex--;
			}
		}
		else if(cityA->indexOnSolution > cityB->indexOnSolution){
			int aux = cityB->nextStop->indexOnSolution;
			int end = cityA->nextStop->indexOnSolution;

			//On the nodes:
			City* temp = cityB->nextStop;
			cityB->nextStop = cityA;
			temp->nextStop = cityA->nextStop;

			curIndex = cityA->indexOnSolution;
			while(true){
				if(curIndex == temp->indexOnSolution) break;
				cities[solution[curIndex]]->nextStop = cities[solution[curIndex-1]];
				if(curIndex == 0) curIndex = nCities-1;
				else curIndex--;
			}
		}

		curIndex = starter;
		//Fill solution array:
		for (int i = 0; i < nCities; ++i)
		{
			solution[i] = cities[curIndex]->index;
			cities[curIndex]->indexOnSolution = i;
			curIndex = cities[curIndex]->nextStop->index;
		}
	}

};
