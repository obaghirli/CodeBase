#include "SurveyClass.h"
#include "LinkedList.h"


#include <map> //this is how i store (color, count) structure
#include <sstream> //this I needed to do the rounding for the float, there might be other methods, but this was more intuitive
#include <iomanip> //again for the rounding, specially to use the fixed keyword and setprecision() function

//set pointers to null to avoid dangling pointers
SurveyClass :: SurveyClass(){
	members = NULL;
}

//copy constructor 
//if rhs not empty, copy it to the lhs, via deep copy since LinkedList constructor does the deep copy
SurveyClass :: SurveyClass(const SurveyClass &other) {
	if (other.members != NULL){
		this->members = new LinkedList( *(other.members) );
	} else {
		this->members = NULL;
	}
}

SurveyClass& SurveyClass :: operator=(const SurveyClass& list) {
	//lhs might be not empty, so we need to ensure that it is empty before the assignment 
	if(this->members){
		delete this->members;
	}

	this->members = NULL;

	//same code as of the copy constructor
	if(list.members != NULL){
		this->members = new LinkedList( *(list.members) );
	} else {
		this->members = NULL;
	}

	//return updated object to be able to do this: S1=(S2=S3)
	return *this;
}

SurveyClass :: ~SurveyClass(){

	if(members){
		delete members;
	}

	members = NULL;
}

//this is the driver function for the LL class method pushTail()
//if members was null, which is the case for the first time addition,
//then instantiate it with an empty LL
//so that we can use LL method pushTail correspondingly
void SurveyClass :: addMember(const Member& newMember) {

	if(members == NULL){
		members = new LinkedList();
	}	

	members->pushTail( newMember );

}

//tis is how I do the float rounding
float convert (float fl){

	stringstream stream;
	stream << setprecision(2) << fixed <<fl;
	stream >> fl;
	return fl;

}


// traverse over the LL if not empty and calculate the average 
float SurveyClass :: calculateAverageAge() {

	float average = 0.00;
	int sum = 0;
	int size = 0; //length of the LL

	if (this->members != NULL){
		size = (this->members)->length;
	}

	if (this->members != NULL){
		Node* head = (this->members)->head;
		Node* current = head;

		while (current != NULL) {
			sum = sum + (current->data).age;
			current = current->next;
		}

		if (size != 0){ //just in case to avoid division by zero
			average = float(sum)/size;
		}

		return convert(average);

	} else {
		//if LL was empty, return 0.00, in case input file has zero entry
		return 0.00;

	}


}


//create an empty map, with key value pairs, key being the color, value being the count
//as you go over the LL and see the color enties, check if it already exists in the map
//if no, add it with value 1 (means that i encountered it only once)
//if yes, increment the count
//lastly traverse the map with an iterator, and return the key, with maximum count
string SurveyClass :: findMostFavouriteColor() {

	pair<string, int> temp;
	pair<string, int> max;

	pair<string, int> t;
	map<string, int> m;
	map<string, int> :: iterator it=m.begin();

	if (this->members != NULL) {

		Node* head = (this->members)->head;
		Node* current = head;

		if (current != NULL) {
			while(current != NULL){

				t.first = (current->data).color;
				t.second = 1;
				it = m.find(t.first);
				if ( it == m.end() ){
					m.insert(t);
				} else {
					(it->second)++;
				}

				current = current->next;
			}

			max = *(m.begin()); // max is the tuple (key, value), initially assigned with the first entry in the map
			for (it = m.begin(); it != m.end(); it++){
				temp = *it;
				if ( temp.second > max.second ){
					max = temp;
				}

			}

			return max.first;
			
		} else {
			// if the mmebers is not empty, but LL it points to is empty aka input file is empty, return empty string,
			return "";
		}

	} else {
		// if the mmebers is empty, aka input file is empty, return empty string,
		return "";

	}

}
