#include "Application.h"

Application::Application() :m_window(nullptr), m_gameover(false), m_clearColor{ 1,1,1,1 }, m_runningTime(0){}
Application::~Application()
{
}

void Application::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	glfwInit();
	m_window = glfwCreateWindow(720, 720, "tittle", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	ogl_LoadFunctions();
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	startup();
	while (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update(1);
		draw();
		glfwSwapBuffers(m_window);
		glfwPollEvents();

	}

	shutdown();
}

void Application::clearScreen()
{
}