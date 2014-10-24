#include <iostream>

template <class V>
class heap
{
  private:
    V** pointer;//stores address for each index
    V* value; //stores index's value
    int* index; //stores indexes
    V inf;
    int nElements;
    int starter;

  public:
    heap(){
    }

    heap(int size, V arg){
    	nElements = size-1;
      value = new V[size];
      pointer = new V*[size];
      index = new int[size];
      starter = arg;
      for(int i = 0; i<size; i++){
        value[i] = arg;
        index[i] = i;
        pointer[i] = &(value[i]);
        //arg++;
      }
    }
	
		//Receives the element's index
    void swap(int index_a, int index_b){
    	int slot_a = getValueIndex(index_a); 
    	int slot_b = getValueIndex(index_b);
      int drafti = index[slot_a];
      index[slot_a] = index[slot_b];
      index[slot_b] = drafti;
      
      V *a = pointer[index_a];
      V *b = pointer[index_b];
      V draft = *a;
      *a = *b;
      *b = draft;
      
      V* draftp = pointer[index_b];
      pointer[index_b] = pointer[index_a];
      pointer[index_a] = draftp;
    }

    V peek(int i){
      return *(pointer[i]);
    }

    V vpeek(int i){
      return value[i];
    }
    
    //Given a 
    int getValueIndex(int i){
      return (int)(pointer[i]-value);
    }
    
    void heap_up(int slot){//receives element's address (value)
    	if(slot>0){
    		if(value[slot]<value[((slot-1)/2)]){
					swap(index[slot], index[((slot-1)/2)]);
					heap_up(((slot-1)/2));
				}
    	}
    }
    
    void heap_down(int slot){//receives element's address (value)
    	int child;
    	if(((2*slot)+1)>nElements){
    		return;
    	}
    	else if(((2*slot)+1)<nElements){
    		if(value[(2*slot)+2]<value[(2*slot)+1]) child = (2*slot)+2;
    		else child = (2*slot)+1;
    	}
    	else if(((2*slot)+1)==nElements){
    		child = (2*slot)+1;
    	}
    	
    	if(value[child]<value[slot]){
    		swap(index[child], index[slot]);
    		heap_down(child);
    	}
    }
    
    void insert(V v){
    	value[nElements] = v;
    	heap_up(nElements);
    	return;
    }
    
    void erase(int i){//receives element's index (find address through pointer[])
    	int slot = getValueIndex(i);
    	value[slot] = starter;//makes value infinite
    	swap(i, index[nElements]);//swaps it with last one
    	
    	//fix heap:
    	if(value[slot]<value[((slot-1)/2)]) heap_up(slot);
    	else if (value[slot]>value[(2*slot)+1]||value[slot]>value[(2*slot)+1]){
    		heap_down(slot);
    	}
    	
    	return;
    	
    }
    
    void replace(int i, V v){
    	erase(i);
    	insert(v);
    	return;
    }
    
    V top_value(){
    	return value[0];
    }
    
    int top_index(){
    	return index[0];
    }

		/*
    void update(int i, V v){//i = index to pointer[]
			int slot = getValueIndex(i);//find where element i's index in value[]
			value[slot] = v;
			if(value[slot]<value[((slot-1)/2)]){
				swap(index[slot], index[((slot-1)/2)]);
				
				autoupdate(slot);
			}
			int r_child = value[2*slot+2]; 
			int l_child = value[2*slot+1];
			
			
    }
	 */

    ~heap(){}
};

/*
  iParent     = floor((i-1) / 2)
  iLeftChild  = 2*i + 1
  iRightChild = 2*i + 2
*/
