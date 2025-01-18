#include "CDList.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
void CDList<T>::getJosephusPosition(int m)
{
	//Declare two pointers which point to two nodes and set them equal to head
	

	//Loop until there is only one node
	

	//Declare a counter and set equal to 1
	

	//Loop until counter equals m
	

	//Set second pointer equal to first pointer and first pointer to the next node 
	

	//Declare a temp node pointer and set equal to first pointer
	

	//Print value of node to be deleted
	

	//Relink nodes and erase temp node
	

	//Print value of last node
	

}

int main()
{
	CDList<string> sentence;
	CDList<string>::Iterator word = sentence.begin();

	for (int i = 0; i < 8; i++)
	{
		sentence.push_back("Person " + to_string(i + 1));
	}

	sentence.getJosephusPosition(2);
}
