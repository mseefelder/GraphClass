
template <class V>
class heap
{
  private:
    V** pointer;
    V* value;
  public:
    heap(){
    }

    heap(int size, V starter){
      value = new V[size];
      pointer = new V*[size];
      for(int i = 0; i<size; i++){
        value[i] = starter;
        pointer[i] = &(value[i]);
        starter++;
      }
    }

    void swap(int index_a, int index_b){
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

    void update(int i, V v){
      
    }

    ~heap(){}
};

/*
  iParent     = floor((i-1) / 2)
  iLeftChild  = 2*i + 1
  iRightChild = 2*i + 2
*/
