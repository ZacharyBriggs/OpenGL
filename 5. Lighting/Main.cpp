#include "LightingApplication.h"
int main()
{
	Application* app = new LightingApplication();
	app->run("bob", 800, 600, false);
}