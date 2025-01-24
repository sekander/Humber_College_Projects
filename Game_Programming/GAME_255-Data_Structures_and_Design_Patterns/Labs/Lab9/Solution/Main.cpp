#include "Window.h"

int main(int argc, char** argv)
{
	Window* w = new Window("Event Notifier", 200, 200);

	delete w;

	return 0;
}
