#include "Application.h"
#include "Transform.h"
#include "Shader.h"
#include "MeshRenderer.h"

class GUIApplication : public Application
{
public:
	MeshRenderer* m_mesh;
	Shader* m_defaultShader;
	Transform* m_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 translation = glm::mat4(1);
	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};
