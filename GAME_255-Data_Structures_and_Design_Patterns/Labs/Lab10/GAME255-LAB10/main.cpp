#include <iostream>

#include "Game.h"
#include "GuessingGame.h"

using namespace std;

int main() 
{
	GuessGame  guessServer;
	Momento *momento;

	const int  MAX = 3;
	Game games[MAX];
	int  gamesComplete = 0;
	int  guess, ret;

	for (int i=0; i < MAX; i++) 
	{
		cout << "Enter name: " ;
		cin >> games[i].name;
		
		//INSERT CODE HERE
		//Set the momento object equal to the momento returned by the GuessGame object after using the join member function
		

		//INSERT CODE HERE
		//Insert the momemnto into the games array at index i
		
	}

	while (gamesComplete != MAX) 
	{
		for (int j=0; j < MAX; j++) 
		{
			if (games[j].done) 
				continue;

			cout << games[j].name <<" ("<<games[j].min <<'-'<<games[j].max <<"): ";
			cin >> guess;
		
			//INSERT CODE HERE
			//Set the ret variable equal to the GuessGame value returned from using the evaluateGuess member function
			

			//INSERT CODE HERE
			//If ret equals 0
			
				//INSERT CODE HERE
				//Print a winning message
				

				//INSERT CODE HERE
				//Set the games done variable to 1
				

				//INSERT CODE HERE
				//Add 1 to gamesCompleted
				

			//INSERT CODE HERE
			//Else if ret is less than 0
			
			
				//INSERT CODE HERE
				//Print too low message
				
				
				//INSERT CODE HERE
				//Set the games min to guess
				
			
			//INSERT CODE HERE
			//Else
				
				//INSERT CODE HERE
				//Print too high message
				

				//INSERT CODE HERE
				//Set the games max to guess
				
			
		}	
	}  
	
	delete momento;

	system("pause");

	return 0;
}