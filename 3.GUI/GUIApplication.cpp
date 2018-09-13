#include "GUIApplication.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/fwd.hpp"
#include "glm/glm/ext.hpp"
#include "imgui.h"

void GUIApplication::startup()
{
}

void GUIApplication::shutdown()
{
}

void GUIApplication::update(float dt)
{
}

void GUIApplication::draw()
{
	ImGui::Text("hello");
}