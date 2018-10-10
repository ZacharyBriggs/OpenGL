#pragma once
#include "Application.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/fwd.hpp"
class MeshRenderer;
class Shader;
class DirectionalLight;
class Geometry;
class TextureApplication : public Application
{
	typedef void(*KeyFunc)(GLFWwindow *window, int key, int scancode, int action, int mods);
public:
	TextureApplication();
	~TextureApplication();
	MeshRenderer* mesh;
	Shader* defaultShader;
	Geometry* geo;
	DirectionalLight* DaLight;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
protected:
	void startup() override;
	void shutdown() override;
	void update(float dt) override;
	void draw() override;
};

