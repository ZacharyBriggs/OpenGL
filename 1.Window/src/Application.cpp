#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include <imgui_impl_glfw_gl3.h>

Application::Application() :m_window(nullptr), m_gameover(false), m_clearColor{ 1,1,1,1 }, m_runningTime(0){}
Application::~Application()
{
}

void Application::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	float prevTime = glfwGetTime();
	glfwInit();
	m_window = glfwCreateWindow(720, 720, title, NULL, NULL);
	glfwMakeContextCurrent(m_window);
	ogl_LoadFunctions();
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	ImGui_ImplGlfwGL3_Init(m_window, true);
	startup();
	while (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear frame buffer
		double glfwTime = glfwGetTime();

		glfwPollEvents();

		ImGui_ImplGlfwGL3_NewFrame();


		update(glfwTime);

		draw();
		ImGui::Render();
		glfwSwapBuffers(m_window);//swap the buffer for this window


		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE))
		{
			m_gameover = true;
		}

		if (m_gameover)
			shutdown();

	}

	shutdown();
}

void Application::clearScreen()
{
}