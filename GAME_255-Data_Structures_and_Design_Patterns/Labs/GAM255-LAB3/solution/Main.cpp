/* For this project to work with template classes
   set Project Properties -> Configuration Properties -> C/C++ -> Language -> Conformance mode = No */

#include <iostream>

using namespace std;

#include "PriorityQueue.h"

int main(void)
{
	int key;
	PriorityQueue<int> pq;

	for(int i = 0; i < 5; i++)
	{
		key = 5 - i;
		pq.push(key, i);

		cout << "Pushed Priority " << key << ": " << i << endl;
	}

	while(!pq.empty())
	{
		cout << "Value: " << pq.peek() << endl;
		pq.pop();
	}

	system("pause");

	return 0;
}
