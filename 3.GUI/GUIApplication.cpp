#include "GUIApplication.h"
#include <imgui.h>

GUIApplication::GUIApplication()
{
}

GUIApplication::~GUIApplication()
{
}

void GUIApplication::startup()
{
}

void GUIApplication::update(float dt)
{
}

void GUIApplication::draw()
{
	ImGui::Text("hello world");
}

void GUIApplication::shutdown()
{
}
