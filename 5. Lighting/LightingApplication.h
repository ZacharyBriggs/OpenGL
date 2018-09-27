#pragma once
#include "Application.h"
class LightingApplication : public Application
{
public:
	LightingApplication();
	~LightingApplication();
protected:
	void startup() override;
	void shutdown() override;
	void update(float dt) override;
	void draw() override;
};

