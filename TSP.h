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

		curIndex = starter;
		//Fill solution array:
		solution = new int[nCities];
		for (int i = 0; i < nCities; ++i)
		{
			solution[i] = cities[curIndex]->index;
			cities[curIndex]->indexOnSolution = i;
			curIndex = cities[curIndex]->nextStop;
		}

		solved = true;
		return;
	}

	//Each vertex has an edge associated with it. We have N=nCities edges.
	//If we check for each edge if it crosses another edge, we have N**2 checks. (reasonable)
	void twoOpt(){
		double totalDistance = solutionDistance();
		int i, j;
		double aux = 0.0;

		repeat:
		i = 0; 
		j = 0;
		for (i; i < nCities; ++i)
		{
			for (j; j < nCities; ++j)
			{
				if (pathsCross(cities[i],cities[j]))
				{
					aux = totalDistance 
					- (edgeLength(cities[i]) + edgeLength(cities[j])) 
					+ (distance(cities[i], cities[j]->nextStop) + distance(cities[j],cities[i]->nextStop));

					if(totalDistance > aux){
						twoOptSwap(cities[i],cities[j]);
						totalDistance = aux;
						goto repeat;
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

	//compute distance from one city to another
	double distance(City* cityA, City* cityB){

	}

	double edgeLength(City* city){
		//...
	}

	double solutionDistance(){
		//...
	}

	//Check if two pths between two pairs of cities cross each other
	// http://ideone.com/PnPJgb
	//PROBLEM MUST BE SOLVED
	bool pathsCross(City* cityA, City* cityB){
		PointF CmP = new PointF( cityB->pos[0] - cityA->pos[0], cityB->pos[1] - cityA->pos[1]);
		PointF r = new PointF( cityA->nextStop->pos[0] - cityA->pos[0], cityA->nextStop->pos[1] - cityA->pos[1]);
		PointF s = new PointF( cityB->nextStop->pos[0] - cityB->pos[0], cityB->nextStop->pos[1] - cityB->pos[1]);
 
		double CmPxr = ( cityB->pos[0] - cityA->pos[0]) * ( cityA->nextStop->pos[1] - cityA->pos[1]) - ( cityB->pos[1] - cityA->pos[1]) * ( cityA->nextStop->pos[0] - cityA->pos[0]);
		double CmPxs = ( cityB->pos[0] - cityA->pos[0]) * ( cityB->nextStop->pos[1] - cityB->pos[1]) - ( cityB->pos[1] - cityA->pos[1]) * ( cityB->nextStop->pos[0] - cityB->pos[0]);
		double rxs = ( cityA->nextStop->pos[0] - cityA->pos[0]) * ( cityB->nextStop->pos[1] - cityB->pos[1]) - ( cityA->nextStop->pos[1] - cityA->pos[1]) * ( cityB->nextStop->pos[0] - cityB->pos[0]);
		 
		if ( CmPxr == 0f)
		{
		// Lines are collinear, and so intersect if they have any overlap
		 
		return ( ( cityB->pos[0] - cityA->pos[0] < 0f) != ( cityB->pos[0] - cityA->nextStop->pos[0] < 0f))
		|| ( ( cityB->pos[1] - cityA->pos[1] < 0f) != ( cityB->pos[1] - cityA->nextStop->pos[1] < 0f));
		}
		 
		if ( rxs == 0f)
		return false; // Lines are parallel.
		 
		double rxsr = 1f / rxs;
		double t = CmPxs * rxsr;
		double u = CmPxr * rxsr;
		 
		return (t >= 0f) && (t <= 1f) && (u >= 0f) && (u <= 1f);
	}

	//INCOMPLETE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//ONLY CALLED BY twoOpt(): swapping operation when paths cross
	void twoOptSwap(City* cityA, City* cityB){
		//Here I have to do the path swap on the nodes and on the solution array!
		
		//On the nodes:
		City* temp = cityA->nextStop;
		cityA->nextStop = cityB->nextStop;
		cityB->nextStop = temp;
		
		//On the solution array:


	}


};

/*

TO DO:

twoOptSwap();
edgeLength();
distance();
solutionDistance();

*/