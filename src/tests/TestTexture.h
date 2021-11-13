#pragma once
#include"test.h"
#include"memory"
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"



namespace test {
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float _color[4];
		std::unique_ptr < VertexArray> va;
		std::unique_ptr < VertexBuffer> vb;
		std::unique_ptr < IndexBuffer> ib;
		std::unique_ptr < Shader> shader;
		std::unique_ptr < Texture> texture;
		std::unique_ptr<glm::vec3> model_translatorA;
		std::unique_ptr<glm::vec3> model_translatorB;
		std::unique_ptr<Renderer> renderer;
	};
}
