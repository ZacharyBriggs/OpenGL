#pragma once
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include "stdio.h"
struct GLFWwindow;
class Application
{
	
public:
	Application();
	virtual ~Application();
	void run(const char * title, unsigned int width, unsigned int height, bool fullscreen);
	void clearScreen();
protected:
	virtual void startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;
	GLFWwindow* m_window;
	bool m_gameover;
	float m_clearColor[4];
	float m_runningTime;

};