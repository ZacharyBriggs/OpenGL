#include "IntroApplication.h"
int main()
{
	Application* app = new IntroApplication();
	app->run("bob", 800, 600, false);
}