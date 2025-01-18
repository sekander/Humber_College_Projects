#include "Controller.h"
#include <memory>

//Declare a static STL vector of Controller Pointers
//Name it _instance


Controller::Controller() 
{
	//Check if vector is empty
	if(_instance.empty())
		_instance.reserve(4);


	//Allocate vector memory by reserving the vector Controller locations
	//Use vector's reserve(size) member function
	

	cout << "Controller Constructor" << endl;
}

Controller::~Controller() 
{
	cout << "Controller Destructor" << endl; 
}

Controller* Controller::getInstance()
{
	//Check if the vector is less than 4
	if(_instance.size() < 4)	
	{
		//Instantiate a temporary auto_ptr for Controller
		std::auto_ptr<Controller> controller (new Controller());
		Controller *c = new Controller();

	//Push the controller pointer into the vector

		_instance.push_back(c);
		//_instance.push_back(controller);
		

	
		cout << "Controller " << _instance.size() << " returned" << endl;
	}
	//Else 
	else
	{
	
		cout << "Controller Exists" << endl;

		//Return the last item in the vector
		return _instance.back();
	}	

	
	
}
