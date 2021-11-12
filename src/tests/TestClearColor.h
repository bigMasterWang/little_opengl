#pragma once
#include"test.h"
namespace test {
	class TestCleraColor : public Test
	{
	public:
		TestCleraColor();
		~TestCleraColor() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float _color[4];
	};
}
