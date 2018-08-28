#include "IntroApplication.h"
#include <utility>

IntroApplication::IntroApplication()
{
}

IntroApplication::~IntroApplication()
{
}

void IntroApplication::startup()
{
	Gizmos::create();
}

void IntroApplication::shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void IntroApplication::update(float dt)
{
	model[1].z += cos(.1);
}

void IntroApplication::draw()
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
	Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 15, 10, glm::vec4(1, 1, 1, 1), &model);
	Gizmos::draw(projection * view);

}
