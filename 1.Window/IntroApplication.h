#pragma once
#include "Transform.h"
#include "Application.h"
#include "FlyCamera.h"

class IntroApplication : public Application
{
public:
	IntroApplication();
	~IntroApplication();
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection;
	Transform *trans = new Transform;
	FlyCamera* cam = new FlyCamera;
protected:
	void startup() override;
	void shutdown() override;
	void update(float dt) override;
	void draw() override;
};
