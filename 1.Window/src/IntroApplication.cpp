#include "IntroApplication.h"
#include <utility>
#include "Gizmos.h"
#include "FlyCamera.h"
#include "Transform.h"

IntroApplication::IntroApplication()
{
}

IntroApplication::~IntroApplication()
{
}

void IntroApplication::startup()
{
	Gizmos::create();
	trans->SetModel(glm::mat4(1));
	cam->setOrthographicView(50,-50,50,-50,1000.0f,0.1f);
	//cam->setPerspectiveView(90,1920/1080.0f,0.1f,1000.0f);
}

void IntroApplication::shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void IntroApplication::update(float dt)
{
	trans->Rotate(90, glm::vec3(0, 1, 0));
	cam->update(m_window, dt);
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
	Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 15, 10, glm::vec4(1, 0, 0, 1), &trans->GetModel());
	glm::mat4 a = cam->getWorldTransform();
	glm::mat4 b = cam->getView();
	glm::mat4 c = cam->getProjection();
	Gizmos::draw(cam->getProjection() * cam->getView() * cam->getWorldTransform());

}
