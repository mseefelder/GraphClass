#include "linkedlist.h"

//function definitions
    
    //Get number of elements:
    int linkedList::getSize()
    {
        return size;
    }
    
    //Insert node:-----------------------------
    ReturnCode linkedList::insert(int newValue) //includes user 'a' in list 't' 
    {
        Node *newNode;
        
        //WARNING - Not checking if index or sock already exists.
        //In our application it won't be necessary
        
        // 1. Create new node on memory
        
        newNode = new Node;
        if (newNode == NULL) return INSUFFICIENT_MEMORY;
        
        // 2. Attributes the new user to this node
        
        newNode->value = newValue;
        newNode->index = size; 
        // 3. New node gets in the list right after index '-1'(head)
        
        newNode->nextNode = head->nextNode;
        newNode->prevNode = head;
        
        // head nextNode points to the new node
        
        if(head->nextNode) head->nextNode->prevNode = newNode;
        head->nextNode = newNode;
        size++;
        
        // 5. Returns it was successfull
        
        return INSERTION_SUCCESS;
    }
    
    //Searches---------------------------------
    
    //Get full user from index
    int linkedList::getValue(int index)
    {
        Node *p;
        
        for (p=head; p; p=p->nextNode)
        {
            if (p->index == index) return (p->value);
        }
        return -1;
    }
    
    //List elements:---------------------------
    
    //List element indices and their respective sockets
    int* linkedList::listAll()
    {
        int element[size];
	int i=0;
               
        Node *p;
        
        printf("\n Next node sequence: \n");
        p=head->nextNode;
        while (p != NULL)
        {
            element[i] = p->value;
            p=p->nextNode;
	    i++;
        }
        
        return element;
    }
    
    /*
Lists all elements in two steps:
  The first shows each element and to wich element its
nextNode pointer points to;
  The second shows each element and to wich element its
prevNode pointer points to;
  Model:
  [ index | username ] ->
*/

    void linkedList::listAllS()
    {
        Node *p;
        
        printf("\n Next node sequence: \n");
        p=head->nextNode;
        while (p->nextNode != NULL)
        {
            printf("[i: %d | name: %d] -> ", p->index, p->value);
            p=p->nextNode;
        }
        printf("[i: %d | name: %d ] next-> ", p->index, p->value);
        printf("\n Previous node sequence: \n");
        for (p; p; p=p->prevNode)
        {
            printf("[%d : %d] -> ", p->index, p->value);
        }
        printf("\n");
    }
  
    //Delete element:----------------------------
    //Searches by index and deletes
    int linkedList::del(int index)
    {
        //
        printf("1");
        if (index<0) return FORBIDDEN_PROCEDURE;
        Node *n, *anterior, *posterior;
        bool found = false;
        anterior = head;
        for(n=head->nextNode; n; n=n->nextNode)
        {
            
            if(n->index == index) {
                found = true;  
                break;      
            }
            //printf("%s\n", n->user.name);
            anterior = n;
        }
        printf("2");
        
        if(found == true)
        {
            anterior->nextNode = n->nextNode;
            
            posterior = n;
            if(posterior->nextNode != NULL)
            {
                posterior = posterior->nextNode;  
                posterior->prevNode = n->prevNode;
            }
            //free(n);
            delete n;
            
            //printf("Index anterior [%d]=",anterior->user.index);
            while(anterior->index > -1)
            {
                //printf("Editando [%d]...\n", anterior->user.index );
                anterior->index -= 1;
                anterior = anterior->prevNode;
            }
            
            size--;
            
            return REMOVAL_SUCCESS;
        }
        else
        {
            return NO_SUCH_USER;
        }
    }

void linkedList::list2Array(int target[])
{
	int i = 0;
	//int element[size];

	Node *p;
    p=head->nextNode;
    while (p->nextNode != NULL)
    {
        target[i] =  p->value;
        p=p->nextNode;
		i++;
    }

	//target = element;
}
