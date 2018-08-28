#pragma once
#include "Transform.h"
#include "Application.h"

class IntroApplication : public Application
{
public:
	IntroApplication();
	~IntroApplication();
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);
	glm::mat4 model = glm::mat4(1);
protected:
	void startup() override;
	void shutdown() override;
	void update(float dt) override;
	void draw() override;
};