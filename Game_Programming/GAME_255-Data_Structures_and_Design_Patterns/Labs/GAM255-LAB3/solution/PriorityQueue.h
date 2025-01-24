#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "SList.h"
#include <iostream>

template <typename T>
class PriorityQueue
{
	// List containing data values
	SList<T> data;

	// List containing priority keys
	SList<int> key;

	


public:
	

	// Insert a data value sorted by priority 
	void push(const int priority, const T& value)
	{
		if(key.size() == 0)
		{
			// if priority queue is empty, insert new node to front of lists
			// INSERT CODE HERE
//			std::cout << "Got Activated\n";
			data.push_front(value);
			key.push_front(priority);
			//data.p;
		}
		else
		{
		// create an iterator for the data and key lists
		// INSERT CODE HERE
		SList<int>::Iterator key_it = key.begin();
		SList<int>::Iterator it = data.begin();
		//auto key_it = key.begin();

		while(!*key_it)
		{
			//NOT SURE IF THIS IS RIGHT
			if(priority >= value)
			{
				key_it++;
			}

			//data.insert(priority, value);
			//data.insert(data.begin(), value);
			//key.insert(key.begin(), priority);
		}	


		data.insert(it, value);
		//NOT SURE WHAT TO INSERT IN THE KEY	
		//key.insert(
		// insert data and key if null
		// INSERT CODE HERE
			



		}
	}

	// Remove first element from priority queue
	// Precondition: Priority queue not empty
	void pop()
	{
		// remove front items from lists
		// INSERT CODE HERE
		key.pop_front();
		data.pop_front();
	}

	// return reference to first value in priority queue
	// precondition: list is not empty
	T& peek()
	{
		// create an iterator and set to beginning of data list
		// use the Iterator begin method to do this
		// INSERT CODE HERE
		SList<int>::Iterator it = data.begin();
		//return data.back();
		//return data[1];
		//return data.begin();
		return *it; 
	}

	// check for empty priority queue
	bool empty() const
	{
		// INSERT CODE HERE
		//return false;
		return data.empty();
	}

	// return number of members
	size_t size() const
	{
		// INSERT CODE HERE
		//return 0;
		return data.size();
	}

	// remove all nodes
	void clear()
	{
		// INSERT CODE HERE
		data.clear();
	}
};

#endif
