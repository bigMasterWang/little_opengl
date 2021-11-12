#include"TestClearColor.h"
#include"GL/glew.h"
#include"imgui/imgui.h"

namespace test {
	TestCleraColor::TestCleraColor() : _color{ 0.0f,0.0f, 0.0f, 0.0f }
	{
	}


	TestCleraColor::~TestCleraColor()
	{

	}
	void TestCleraColor::OnUpdate(float deltaTime)
	{
	}
	void TestCleraColor::OnRender()
	{
		glClearColor(_color[0], _color[1], _color[2], _color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void TestCleraColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", _color);
	}
}
