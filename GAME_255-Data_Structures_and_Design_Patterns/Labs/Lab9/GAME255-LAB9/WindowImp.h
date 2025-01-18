/* 
	Class:		WindowImp
	Purpose:	Implements glut window and mouse functionality
				Registers mouse events and handles the event during glut mouse callback
*/

#ifndef WINDOWIMP_H
#define WINDOWIMP_H

#include <string>
#include <gl/glut.h>

#include "EventHandler.h"
#include "MouseEvent.h"

using namespace std;

class WindowImp
{
	public:
		WindowImp(string title, int width, int height)
		{
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
			glutInitWindowSize(width, height);
			glutCreateWindow(title.c_str());
			glutDisplayFunc(&WindowImp::initDisplay);
			
			glutMouseFunc(&WindowImp::glutMouse);
			glutMotionFunc(&WindowImp::glutMouseMotion);

			//INSERT CODE HERE
			//Register MOUSE_PRESSED event with respective callback member function onPress
			//USE _handler->registerEventFunc to do this			
			

		
			//INSERT CODE HERE
			//Register MOUSE_RELEASED event with respective callback member function onRelease
			//USE _handler->registerEventFunc to do this
			

			////INSERT CODE HERE
			////Register MOUSE_MOVED event with respective callback member function onMouseMove
			////USE _handler->registerEventFunc to do this
			

		}

		void draw()
		{
			glutMainLoop();
		}

	private:
		//Component event handler object used to register and handle events
		static EventHandler* _handler;
	
		static void initDisplay()
		{
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glutSwapBuffers();
		}

		virtual void onPress(const MouseEvent* event)
		{ }

		virtual void onRelease(const MouseEvent* event)
		{ }

		virtual void onMouseMove(const MouseEvent* event)
		{ }

		//Callback method invoked by glutMouseFunc
		//Instantiates MouseEvent and handles event
		//INSERT CODE IN THIS METHOD
		static void glutMouse(int glutButton, int glutState, int glutX, int glutY)
		{
			//Instantiate a MouseEvent pointer
			

			//Declare a string named state 
			

			//Set the event new position to the glut x and y coordinates
			

			//Set event's state to the glut button and state, and set state equal to it
			

			//Use _handler to handle the event
			
		}

		//Callback method invoked by glutMotionFunc
		//Instantiates MouseEvent and handles event
		//INSERT CODE IN THIS METHOD
		static void glutMouseMotion(int glutX, int glutY)
		{
			//Instantiate a MouseEvent pointer
			

			//Declare a string named state and set it equal to the event MOUSE_MOVED
			


			//Set the new position for event equal to the glut x and y coordinates
			


			//Use _handler to handle the event
			

		}
};

EventHandler* WindowImp::_handler = new EventHandler();

#endif