#include "GUIApplication.h"

int main()
{
	Application* app = new GUIApplication();
	app->run("bob", 800, 600, false);
}