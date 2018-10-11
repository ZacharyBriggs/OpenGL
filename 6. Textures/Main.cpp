#include "TextureApplication.h"
int main()
{
	Application* app = new TextureApplication();
	app->run("text", 800, 600, false);
}