#pragma once
#include "Application.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/fwd.hpp"

class MeshRenderer;
class Shader;
class DirectionalLight;
class Geometry;

class LightingApplication : public Application
{
public:
	LightingApplication();
	~LightingApplication();
	MeshRenderer* mesh;
	MeshRenderer* mesh2;
	MeshRenderer* lightSphere;
	Shader* defaultShader;
	Geometry* geo;
	DirectionalLight* DaLight;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
protected:
	void startup() override;
	void shutdown() override;
	void update(float dt) override;
	void draw() override;
};

