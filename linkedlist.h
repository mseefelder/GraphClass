#include <stdio.h>

typedef enum
{
    INSERTION_SUCCESS    = 100,
    INSUFFICIENT_MEMORY     = 101,
    DUPLICATE_SOCKET      = 102,
    
    REMOVAL_SUCCESS    = 200,
    NO_SUCH_USER = 201,
    
    FORBIDDEN_PROCEDURE      = 300
}ReturnCode;

typedef struct Node
{
    int index;
    int value;
    struct Node *nextNode; //points to an older node
    struct Node *prevNode; //points to a newer node
} Node; 

/*
Create list:
  List is created with a fake user, with the invalid index -1.
  This fake user is used to store our number of elements on the
'sock' field.
*/
class linkedList
{
	public:
	linkedList()
	{
		head = new Node;
		head->index = -1;
		head->value = -1;
		head->prevNode = NULL;
		head->nextNode = NULL;
		size = 0;
	}
	/*
    Node *newList()
    {
        Node *newNode;
        int index;
        
        index = -1; //invalid index for operations. only read by getElNum()
        
        newNode = new Node;
        
        newNode->user = newuser;
        newNode->nextNode = NULL;
        newNode->prevNode = NULL;
        
        //printf("lista criada");
        return newNode;
    }
    */
    
    //Get number of elements:
    int getSize();
    
    //Insert node:-----------------------------
    ReturnCode insert(int newValue);
    //Searches---------------------------------
    
    //Get full user from index
    int getValue(int index);

    //List elements:---------------------------
    
    //List element indices and their respective sockets
    int* listAll();

    //Converts linkedList to int array:
    void list2Array(int target[]);
    
    /*
Lists all elements in two steps:
  The first shows each element and to wich element its
nextNode pointer points to;
  The second shows each element and to wich element its
prevNode pointer points to;
  Model:
  [ index | username ] ->
*/
    void listAllS();
    
    //Delete element:----------------------------
    //Searches by index and deletes
    int del(int index);
    
    ~linkedList()
    {
    	if(head){
    		int i = 0;
    		for(i=0;i<size;i++){
    			this->del(i);
    		}
    		delete head;
    	}
    }
        
    private:
    
    Node* head;
    int size;
};
    
