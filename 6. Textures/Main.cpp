#include "TextureApplication.h"
int main()
{
	Application* app = new TextureApplication();
	app->run("text me", 800, 600, false);
}