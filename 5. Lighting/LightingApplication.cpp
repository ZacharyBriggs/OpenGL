#include "LightingApplication.h"
#include <utility>
#include "Gizmos.h"
#include "glfw/glfw3.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/fwd.hpp>


LightingApplication::LightingApplication()
{
}


LightingApplication::~LightingApplication()
{
}

void LightingApplication::startup()
{
	Gizmos::create();
}

void LightingApplication::shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void LightingApplication::update(float dt)
{
}

void LightingApplication::draw()
{
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}
	Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 15, 10, glm::vec4(1, 0, 0, 1), a);
}
