#ifndef MOUSEADAPTER_H
#define MOUSEADAPTER_H

#include <GL/freeglut_std.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "MouseEvent.h"

using namespace std;

class MouseAdapter
{
	public:
		//Mouse Click Adapter Method
		//INSERT CODE HERE
		static void mouseClicked(int button, int state, int x, int y)
		{
			//Declare a string button state
			string button_state;
			//string MouseEvent:: = "keydown";

			//Set the mouse state to the button and state method parameters
			//Got Confused here would like to resubmit lab with some tips 
			//button_state = MouseEvent::setState(button);
			_mouse->setState(button, state);

			//Set the mouse new position to the x and y coordinate parameters
			//MouseEvent::setNewPos(x, y);
			_mouse->setNewPos(x, y);
			//If state is equal to GLUT_DOWN
			if(state == GLUT_DOWN)
				button_state = "Down";	
			//Set the button state to Down
			else
				button_state = "Up";
			//Else

			//Set the button state to Up

			//Print output similar to mine!
			cout << button_state << endl;
		}

		//Mouse Move Adapter Method
		//INSERT CODE HERE
		static void mouseMoved(int x, int y)
		{
			//Set the mouse old position to be the "new" position, which is stored in _mouse
			_mouse->setOldPos(_mouse->getX(), _mouse->getY());
			//Set the new mouse position to the x and y coodinate parameters
			_mouse->setNewPos(x, y);

			//Print Mouse Drag Button
			cout << _mouse->MOUSE_PRESSED << endl;
			//If _mouse button clicked is left
			if(_mouse->isLeft())
				cout << "left\n";
			//Print left
			else if(_mouse->isRight())
				cout << "right\n";
			else
				cout << "middle\n";

			//Else if _mouse button clicked is right

			//Print right

			//Else
				
			//Print Middle
			cout << _mouse->MOUSE_PRESSED << endl;	
			//Print output similar to mine!
		}

	private:
		static MouseEvent* _mouse;
};

//Instantiate the MouseEvent _mouse instance variable
//INSERT CODE HERE
//MouseAdapter<MouseEvent> 
//MouseEvent* _mouse = new MouseEvent();
MouseAdapter::_mouse = new MouseEvent();

#endif
