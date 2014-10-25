#include <iostream>

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
    
    //insert element at the heap's bottom and sorts it
    //ALWAYS CALLED AFTER ERASE
    void insert(V v){
    
    	value[lastElement] = v;
    	heap_up(lastElement);
    	return;
    	
    }
    
    //Sets element i's value to "starter" and sorts heap.
    //ONLY CALLED BEFORE INSERT
    void erase(int i){ //receives element's index (find address through pointer[])
    	
    	int slot = getValueIndex(i);
    	value[slot] = starter;//makes value infinite
    	swap(i, index[lastElement]);//swaps it with last one
    	
    	//fix heap:
    	if(value[slot]<value[((slot-1)/2)]) heap_up(slot);
    	else if (value[slot]>value[(2*slot)+1]||value[slot]>value[(2*slot)+1]){
    		heap_down(slot);
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
      starter = arg;
      
      //Initialize arrays
      for(int i = 0; i<size; i++){
        value[i] = arg;
        index[i] = i;
        pointer[i] = &(value[i]);
      }
    }
	
		//Swaps two elements by element index
    void swap(int index_a, int index_b){ //Receives the element's index (maps pointer[])
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
    void heap_up(int slot){//receives element's address (value)
    	if(slot>0){
    		if(value[slot]<value[((slot-1)/2)]){
					swap(index[slot], index[((slot-1)/2)]);
					heap_up(((slot-1)/2));
				}
    	}
    }
    
    //Heap sorting operation to make element descend to the right place
    //	Compares element with minimum possible child
    //  If element's value > child's value: 
    //		swap them
    //		call procedure again for the element
    void heap_down(int slot){ //receives element's address (value)
    
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
    		if(value[(2*slot)+2]<value[(2*slot)+1]) child = (2*slot)+2;
    		else child = (2*slot)+1;
    	}
    	//If left child's index on value[] = last element's index
    	//Then, there is no right child. Choose left child.
    	else if(((2*slot)+1)==lastElement){
    		child = (2*slot)+1;
    	}
    	//----------------------------------------------------------
    	//Compare the element with its child
    	if(value[child]<value[slot]){
    		swap(index[child], index[slot]);
    		heap_down(child);
    	}
    	
    }
    
    //Remove top element from the heap
    void pop(){
    
    	//If there's only 1 element: remove it and return
    	if(lastElement == 0){
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
    	
    	//3 - Fix heap
    	if(value[slot]<value[((slot-1)/2)]) heap_up(slot);
    	else if (value[slot]>value[(2*slot)+1]||value[slot]>value[(2*slot)+1]){
    		heap_down(slot);
    	}
    	
    	//4 - Remove last element (popped element) from heap by:
    	//	4.1 - Making the elements pointer be a NULL pointer
    	pointer[index[lastElement]] = NULL;
    	//	4.2 - Decrease the last element's index
    	lastElement--;
    	
    	return;
    }
    
    //Check if element i is still on the heap
    bool exists(int i){
    	//If the pointer to it is NULL, it was removed
    	if(pointer[i] == NULL) return false;
    	else return true;
    	
    }
    
    //Replace element i's value (and sorts heap)
    void replace(int i, V v){
    	erase(i);
    	insert(v);
    	return;
    }
    
    //Returns value of any element
    V cost(int i){ //receives element's index (find address through pointer[])
    	return value[getValueIndex(i)];
    }
    
    //Returns value of the top element
    V top_value(){
    
    	return value[0];
    	
    }
    
    //Returns index of the top element
    int top_index(){
    
    	return index[0];
    	
    }
    
    //To see if heap is empty
    bool empty(){
    
    	if (lastElement<0) return true;
    	else return false;
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
			//To be implemented...
			return;
    }
		

    ~heap(){}
};

/*
  iParent     = floor((i-1) / 2)
  iLeftChild  = 2*i + 1
  iRightChild = 2*i + 2
*/
