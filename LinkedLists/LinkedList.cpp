#include "LinkedList.h"
#include "Node.h"

//contructor sets the pointer variables to null, in order to avoid dangling pointers
//set length to zero, initially constructed linkedlist with zero length
LinkedList :: LinkedList(){

	length = 0;
	head = 0;
	tail = 0;

}

LinkedList :: LinkedList(const LinkedList &list){

	//deep copy of linkedlist
	//set parameters of the lhs LL to neutral values 
	//when it is copy constructed, it has no parameters assigned yet, 
	//so it is safe and to be safer, we re-neutralize the class parameters  
	head = 0;
	tail = 0;
	length = 0;

	Node* iter  = list.head;

	//if the head of the rhs LL not empty, add it to lhs,
	if (iter != 0){
		head = new Node(iter->data);
		tail = head;
		length++;

		Node* current = head;
		iter = iter->next;

		//if there are some other nodes in the rhs LL, add them as well
		//add via tail
		while (iter != 0){
			tail = new Node( iter->data );
			current->next = tail;
			length++;

			current = current->next;
			iter = iter->next;
		}

	}

}


LinkedList& LinkedList :: operator=(const LinkedList &list){

	//if it is assignment operator, it can well be that it had nodes in it before the assignment
	//there, we need to delete them, in order to establish an empty LL on the lhs.
	if (this->head){
		delete this->head;
	}

	//same code with the copy constructor
	this->head = 0;
	this->tail = 0;
	this->length = 0;

	Node* iter  = list.head;

	if (iter != 0){
		this->head = new Node(iter->data);
		this->tail = this->head;
		(this->length)++;

		Node* current = this->head;
		iter = iter->next;

		while (iter != 0){
			this->tail = new Node( iter->data );
			current->next = this->tail;
			(this->length)++;

			current = current->next;
			iter = iter->next;
		}

	}
	//we need to return the updated lhs LL so we can do this: L1=(L2=L3);
	return *this;
}

void LinkedList :: pushTail(Member data) {

	//if tail is null, it means LL is empty, if so add to tail, and make head point to tail, which is the only node in the LL
	//if not, create a new node after tail, and make tail point to the last node.
	if ( tail == 0) {
		tail = new Node(data);
		head = tail;
		length++;
	} else {
		tail->next = new Node(data);
		tail = tail->next;
		length++;
	}

}

LinkedList :: ~LinkedList(){

	//when LL goes out of scope, need to deallocate dynamically allocated memory inside the LL class
	//that is the head to delete, only if it is not null,
	//and delete head will call the deconstructor of the NODE object, which in turn, will call the deconstructor of the 
	//next node, if it exists, recursively. Then, make parameters NULL, zero, to avoid dangling pointers.
	if (head){
		delete head;
	}

	head = 0;
	tail = 0;
	length = 0;
}