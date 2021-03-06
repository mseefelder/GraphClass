#include <iostream>
#include <limits>
#include <cfloat>

template <class V>
class heap
{
  private:
    V** pointer;//stores address for each index
    V* value; //stores index's value
    int* index; //stores indexes
    V inf;
    int nElements;//stores number of elements -1
    int starter;//starter value (has to be as big as possible)
    int lastElement;//keep record of the actual number of elements
    								//maps index

    //now, some important global flags!-----------------------------------------------------------

    bool upping;
    bool downing;
    int upper;
    int downer;

    //--------------------------------------------------------------------------------------------

    //returns true if x>y
    bool greater(V x, V y){
        if (x == starter){
            if (y == starter)  return false;
            return true;
        }
        if (y == starter) return false;
        return x>y;
    }

    //returns true if x<y
    bool lesser(V x, V y){
        if (x == starter){
            if (y == starter)  return false;
            return false;
        }
        if (y == starter) return true;
        return x<y;
    }

    //insert element at the heap's bottom and sorts it
    //ALWAYS CALLED AFTER ERASE
    void insert(V v){
    	//std::cout<<"inserting "<<v<<"..."<<std::endl;
    	value[lastElement] = v;
    	heap_up(lastElement);
    	return;

    }

    //Sets element i's value to "starter" and sorts heap.
    //ONLY CALLED BEFORE INSERT
    void erase(int i){ //receives element's index (find address through pointer[])
    	//std::cout<<"erase("<<i<<")"<<std::endl;
    	//std::cout<<lastElement+1<<"elements. Bottom element is"<<index[lastElement]<<std::endl;

    	int slot = getValueIndex(i);
    	value[slot] = starter;//makes value infinite
    	swap(i, index[lastElement]);//swaps it with last one

    	//fix heap:
    	if( ((slot-1)/2)>-1 ){

    		//if(value[slot]<value[((slot-1)/2)]) {
            if( lesser(value[slot],value[((slot-1)/2)]) ) {
    			heap_up(slot);
    		}

    		else if( ((2*slot)+1) <= lastElement ){

    			//if (value[slot]>value[(2*slot)+1]||value[slot]>value[(2*slot)+2]){
                if ( greater( value[slot],value[(2*slot)+1] )|| greater( value[slot],value[(2*slot)+2] ) ){
    				heap_down(slot);
    			}

    		}

    	}

    	return;

    }

  public:
  	//Default contructor. Nerver used
    heap(){}

		//Correct contructor
    heap(int size, V arg){
    	nElements = size-1;
    	lastElement = nElements;

    	//allocate arrays
      value = new V[size];
      pointer = new V*[size];
      index = new int[size];

      //Set starter value
      starter = arg;//std::numeric_limits<V>::infinity();
      //std::cout<<"Infinity! "<<starter<<std::endl;

      //Set flags
      upping = false;
      downing = false;
      upper = 0;
      downer = 0;

      //Initialize arrays
      for(int i = 0; i<size; i++){
        value[i] = arg;
        index[i] = i;
        pointer[i] = &(value[i]);
      }
    }

		//Swaps two elements by element index
    void swap(int index_a, int index_b){ //Receives the element's index (maps pointer[])
    	//std::cout<<"Swap:"<<index_a<<"<->"<<index_b<<std::endl;
    	//swap index[a] <-> index[b]
    	int slot_a = getValueIndex(index_a); //Element a's index on value[] and index[]
    	int slot_b = getValueIndex(index_b); //Element a's index on value[] and index[]
      int drafti = index[slot_a];
      index[slot_a] = index[slot_b];
      index[slot_b] = drafti;

      //swap value[a] <-> value[b]
      V *a = pointer[index_a];//value[a]'s address
      V *b = pointer[index_b];//value[b]'s address
      V draft = *a;
      *a = *b;
      *b = draft;

      //swap pointer[a] <-> pointer[b]
      V* draftp = pointer[index_b];
      pointer[index_b] = pointer[index_a];
      pointer[index_a] = draftp;
    }

    //Given an element index, find its index on array "value[]"
    int getValueIndex(int i){
      return (int)(pointer[i]-value);
    }

    //Heap sorting operation to make element ascend to the right place
    //	If element's value < parent's value:
    //		swap them
    //		call procedure again for the element
    void heap_up(int slot_init){//receives element's address (value)
    	bool proceed = true;//-----//
    	int slot = slot_init;//-----//

    	while(proceed){
    		proceed = false;
    		//std::cout<<"Heaping up "<<index[slot]<<std::endl;
    		if(slot>0){
    			//if(value[slot]<value[((slot-1)/2)]){
                if( lesser(value[slot],value[((slot-1)/2)]) ) {
						swap(index[slot], index[((slot-1)/2)]);
						slot = ((slot-1)/2);//-----//
						proceed = true;//-----//
						//heap_up(((slot-1)/2));
					}
    		}
    	}

    	return;
    }

    //Heap sorting operation to make element descend to the right place
    //	Compares element with minimum possible child
    //  If element's value > child's value:
    //		swap them
    //		call procedure again for the element
    void heap_down(int slot_init){ //receives element's address (value)
			bool proceed = true;//-----//
    	int slot = slot_init;//-----//

    	while(proceed){//-----//
    		proceed = false;//-----//
    		//std::cout<<"Heaping down "<<index[slot]<<std::endl;
    		//First we select with wich child we'll compare the element---
    		int child;
    		//If left child's index on value[] > last element's index
    		//This cant happen, so it ends
    		if(((2*slot)+1)>lastElement){
    			return;
    		}
    		//If left child's index on value[] < last element's index
    		//Then, choose minimum valued child
    		else if(((2*slot)+1)<lastElement){
    			//if(value[(2*slot)+2]<value[(2*slot)+1]) child = (2*slot)+2;
                if( lesser(value[(2*slot)+2],value[(2*slot)+1]) ) child = (2*slot)+2;
    			else child = (2*slot)+1;
    		}
    		//If left child's index on value[] = last element's index
    		//Then, there is no right child. Choose left child.
    		else if(((2*slot)+1)==lastElement){
    			child = (2*slot)+1;
    		}
    		//----------------------------------------------------------
    		//Compare the element with its child
    		//if(value[child]<value[slot]){
            if(lesser(value[child],value[slot]) ){
    			swap(index[child], index[slot]);
    			slot = child;//-----//
    			proceed = true;//-----//
    			//heap_down(child);
    		}
    	}


    	return;

    }

    //Remove top element from the heap
    void pop(){

    	//std::cout<<"Heap pop(): \n    ";
    	//If there's only 1 element: remove it and return
    	if(lastElement == 0){
    		//std::cout<<"Only 1 element. Popping..."<<std::endl;
    		pointer[index[0]] = NULL;
    		lastElement--;
    		return;
    	}

    	//Else:
    	int slot = 0;
    	//1 -	Make its value = starter
    	value[slot] = starter;
    	//2 -	swap it with last element
    	swap(index[slot], index[lastElement]);

    	//4 - Remove last element (popped element) from heap by:
    	//	4.1 - Making the elements pointer be a NULL pointer
    	pointer[index[lastElement]] = NULL;
    	//	4.2 - Decrease the last element's index
    	lastElement--;

    	//3 - Fix heap
    	if(((2*slot)+1)<=lastElement){
    		if (value[slot]>value[(2*slot)+1]||value[slot]>value[(2*slot)+2]){
    			heap_down(slot);
    		}
    	}

    	return;
    }

    //Check if element i is still on the heap
    bool exists(int i){
    	//If the pointer to it is NULL, it was removed
    	if(pointer[i] == NULL) {
    		//std::cout<<"Element "<<i<<" doesn't exist."<<std::endl;
    		return false;
    	}
    	else {
    		//std::cout<<"Element "<<i<<" exists."<<std::endl;
    		return true;
    	}

    }

    //Replace element i's value (and sorts heap)
    void replace(int i, V v){
    	//std::cout<<"Replacing "<<i<<"'s value: "<<v<<std::endl;
    	erase(i);
    	insert(v);
    	//std::cout<<"After replace \n   ";
    	//printHeap();
    	return;
    }

    //Returns value of any element
    V cost(int i){ //receives element's index (find address through pointer[])
    	//std::cout<<"["<<i<<"] -> cost = "<<std::endl<<value[getValueIndex(i)];
    	//std::cout<<std::endl;
    	return value[getValueIndex(i)];
    }

    //Returns value of the top element
    V top_value(){
    	//std::cout<<"Top value is:"<<value[0]<<std::endl;
    	return value[0];

    }

    //Returns index of the top element
    int top_index(){
    	//std::cout<<"Top element's index is:"<<index[0]<<std::endl;
    	return index[0];

    }

    //To see if heap is empty
    bool empty(){

    	if (lastElement<0) {
    		return true;
    	}
    	else {
    		//std::cout<<"Heap not empty"<<std::endl;
    		return false;
    	}
    }

    //Prints a line with each element's value
    void printTable(){
		for (int i = 0; i<(nElements+1); i++){
			if (exists(i)) std::cout<<"["<<i<<"]="<<*(pointer[i])<<"; ";
			else 	std::cout<<"["<<i<<"]="<<"---"<<"; ";
		}
	   std::cout<<std::endl;
    }

		//Prints a heap representation, has to be recursive
	void printHeap(){
		std::cout<<"Top: "<<index[0]<<":  ";
		for (int i = 1; i<lastElement+1; i++){
			std::cout<<index[(i-1)/2]<<"<--"<<index[i]<<";  ";
		}
		std::cout<<std::endl;
		return;
    }


    ~heap(){
    	if(value) delete [] value;
    	if(index) delete [] index;
    	if(pointer) delete [] pointer;
    }
};

/*
  iParent     = floor((i-1) / 2)
  iLeftChild  = 2*i + 1
  iRightChild = 2*i + 2
*/
