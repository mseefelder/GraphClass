struct City{
	
	double pos[2];
	int index;
	bool beenTo, left;
	City* nextStop;

	City(){
		pos[0] = 0;
		pos[1] = 0;
		index = 0;
		beenTo = false;
		left = false;
		nextStop = NULL;
	}

	City(double x, double y, int i){
		pos[0] = x;
		pos[1] = y;
		index = i;
		beenTo = false;
		left = false;
		nextStop = NULL;
	}

};

//Traveling Salesman Problem class
class TSP{

public:

	//Loads problem on an array of cities. Just this.
	void open(std::string path){
		
		std::ifstream file;
		file.open(path);
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
			if (dist<minimum)
			{
				startingIndex = i;
				minimum = dist;
		}

		starter = startingIndex;

		return;
	}

	//Dumbest way to solve, just link cities in the order they were read from the problem
	void solveLinear(){
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
				cities[curIndex]->nextStop = cities[starter];
				break;
			}
		}

		solved = true;
		return;
	}

	//Each vertex has an edge associated with it. We have N=nCities edges.
	//If we check for each edge if it crosses another edge, we have N**2 checks. (reasonable)
	void twoOpt(){
		double totalDistance = 0;
		int i, j;
		repeat:
		totalDistance = solutionDistance();
		i = 0; 
		j = 0;
		for (i; i < nCities; ++i)
		{
			for (j; j < nCities; ++j)
			{
				if (pathsCross(cities[i],cities[j]))
				{
					twoOptSwap(cities[i],cities[j]);
					if( !(solutionDistance()<totalDistance) )
					{
						twoOptSwapUndo(cities[i],cities[j]);
					}
					else
					{
						goto repeat; //Yes, I'm using a go to. Deal with it.
						//Ps.: Probably there's a better way to do it. I'm lazy now.
					}
				}
			}
		}
		return;
	}

	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Constructor
	TSP(){}

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

	double distance(City* cityA, City* cityB){

	}

	double edgeRadius(City* city){

	}
	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Check if two pths between two pairs of cities cross each other
	//PROBLEM MUST BE SOLVED
	bool pathsCross(City* cityA, City* cityB){
		//first, check if cities radii intersect. (radii = plural of radius)
		//So, if the distance between two path starting points is smaller
		//than the sum of the paths' radii, the radii intersect
		if(distance(cityA,cityB)<edgeRadius(cityA)+edgeRadius(cityB))
		{
			//Now we have to check if the PATHS intersect:

		}
		else
		{
			return false;
		}

	}
	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//ONLY CALLED BY twoOpt(): swapping operation when paths cross
	void twoOptSwap(City* cityA, City* cityB){
		//Here I have to do the path swap on the nodes and on the solution array!
	}
	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//ONLY CALLED BY twoOpt(): swapping operation when paths cross
	void twoOptSwapUndo(City* cityA, City* cityB){
		//Here I have to undo the path swap on the nodes and on the solution array!
	}


};