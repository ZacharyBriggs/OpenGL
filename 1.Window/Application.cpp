#include "Application.h";
#include <gl_core_4_4.h>;
#include <glfw3.h>;
#include <iostream>;
Application::Application() :m_window(nullptr), m_gameover(false), m_clearColor{ 1,1,1,1 }, m_runningTime(0){}
Application::~Application()
{
}
void Application::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	glfwInit();
	auto window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	ogl_LoadFunctions();
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update(0);
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_1))
			m_gameover = true;
		if (m_gameover)
			shutdown();
	}
}

void Application::clearScreen()
{
}
