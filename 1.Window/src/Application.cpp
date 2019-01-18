#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include <imgui_impl_glfw_gl3.h>
#include <thread>

Application::Application() :m_window(nullptr), m_gameover(false), m_clearColor{ 1,1,1,1 }, m_runningTime(0){}
Application::~Application()
{
}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
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
	auto loopcount = 1;
	while (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		loopcount++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear frame buffer
		double glfwTime = glfwGetTime();

		glfwPollEvents();
		//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		//glfwSetKeyCallback(m_window, key_callback);
		//int state = glfwGetKey(m_window, GLFW_KEY_1);
		//if (state == GLFW_PRESS)
		//	printf("you done did it");
		ImGui_ImplGlfwGL3_NewFrame();


		std::thread UpdateThread(update,glfwTime);
		std::thread DrawThread(draw);
		
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