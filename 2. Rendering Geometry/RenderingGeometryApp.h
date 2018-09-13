#pragma once


class RenderingGeometryApp : public Application
{
public:
	MeshRenderer* mesh;
	Shader* defaultShader;
	RenderingGeometryApp();
	~RenderingGeometryApp();
	unsigned int m_program;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	void startup() override;
	void update(float dt) override;
	void draw() override;
	void shutdown() override;	
};