#include "Application.h"
#include "Transform.h"
#include "Shader.h"
#include "MeshRenderer.h"

class GUIApplication : public Application
{
public:
	MeshRenderer* m_mesh;
	MeshRenderer* m_mesh2;
	Shader* m_defaultShader;
	Transform* m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};
