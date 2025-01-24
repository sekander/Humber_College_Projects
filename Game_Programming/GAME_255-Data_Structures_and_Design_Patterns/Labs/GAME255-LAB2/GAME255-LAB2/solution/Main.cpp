#include "CDList.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
void CDList<T>::getJosephusPosition(int m)
{
	//Declare two pointers which point to two nodes and set them equal to head
	//
	Node* node_1;
	Node* node_2;

	
	node_1 = head;
	node_2 = head;

	int counter = 1;


	while(counter < sz)
	{
		
		node_2 = node_1;
		node_1 = node_1->next;
		Node* tmp = node_1;
		std::cout << tmp->value << " was killed.\n";
		node_1 = tmp->next;
		//delete tmp;
		//sz--;	
		erase(tmp);
	}
	std::cout << "Last Person left standing is " << node_2->value <<std::endl;
	printf("HEHHEHEH I STILL \n");
	

	/*


	//Loop until there is only one node
	int nu_counter = 0;
	while(nu_counter < 7)
	{


	//Declare a counter and set equal to 1
	int counter = 1;
	

	//Loop until counter equals m
//	while(counter <= m)
//	{
	//Set second pointer equal to first pointer and first pointer to the next node 
	node_2 = node_1;
	std::cout << node_1->value << "\n";
	node_1 = node_1->next;	

	std::cout << node_1->value << "\n";
	//Declare a temp node pointer and set equal to first pointer
	Node* tmp;
	tmp = node_1;	
	
	//Print value of node to be deleted
	std::cout << "TMP::" << tmp->value << " was killed. " << sz << " size :: " << this->size() << std::endl;


	//Relink nodes and erase temp node
	//tmp = nullptr;
	node_1 = tmp->next;
//	tmp = nullptr;
	delete tmp;
	sz--;
		
//	counter++;	
//	}


	//Print value of last node
	nu_counter++;
	
//	std::cout << "Node 2::" << node_2->value << " was killed." << std::endl;
	}

	*/

	/*
	//Set second pointer equal to first pointer and first pointer to the next node 
	node_2 = node_1;
	node_1 = node_1->next;	

	//Declare a temp node pointer and set equal to first pointer
	Node* tmp;
	tmp = node_1;	

	//Print value of node to be deleted
	std::cout << "TMP::" << tmp->value << " was killed." << std::endl;
	std::cout << "Node 1::" << node_1->value << " was killed." << std::endl;

	//Relink nodes and erase temp node
	tmp = nullptr;
	delete tmp;	

	//Print value of last node
	
	std::cout << "Node 2::" << node_2->value << " was killed." << std::endl;
	*/	

}

#define MAXXX = 1000;
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

