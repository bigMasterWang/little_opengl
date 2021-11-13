#include"TestTexture.h"
#include"GL/glew.h"
#include"imgui/imgui.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"Renderer.h"
#include"memory"
#include"IndexBuffer.h"
#include"Shader.h"
#include"Texture.h"
#include"VertexArray.h"


namespace test {
	TestTexture::TestTexture() : _color{ 0.0f, 0.0f, 0.0f, 0.0f }
	{
		float position[16] = {
			50.0f, 25.0f, 0.0f, 0.0f,
			100.0f, 25.0f, 1.0f, 0.0f,
			100.0f, 150.0f, 1.0f, 1.0f,
			50.0f, 150.0f, 0.0f, 1.0f
		};


		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		va = std::make_unique<VertexArray>();
		vb = std::make_unique<VertexBuffer>(position, sizeof(float) * 16);

		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);
		va->SetLayout(*vb, layout);


		ib = std::make_unique<IndexBuffer>(indices, 6);
		shader = std::make_unique<Shader>("res/shader/base.shader");

		shader->Bind();
		shader->set_uniform_4f("u_Color", 0.0f, 0.8f, 0.1f, 1.0f);


		// 对图片有很高的要求, 有的就是不行
		texture = std::make_unique<Texture>("res/texture/gj.jpg");
		texture->Bind();
		shader->set_uniform_1i("u_texture", 0);

		renderer = std::make_unique<Renderer>();



		model_translatorA = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
		model_translatorB = std::make_unique<glm::vec3>(100.0f, 0.0f, 0.0f);
	}


	TestTexture::~TestTexture()
	{

	}
	void TestTexture::OnUpdate(float deltaTime)
	{
	}
	void TestTexture::OnRender()
	{
		va->Unbind();
		vb->Unbind();
		ib->Unbind();
		shader->Unbind();


		glClearColor(_color[0], _color[1], _color[2], _color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void TestTexture::OnImGuiRender()
	{
		va->Bind();
		ib->Bind();
		shader->Bind();

		glm::mat4 proj = glm::ortho(0.0f, 200.0f, 0.0f, 200.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));


		//shader.set_uniform_4f("u_Color", r, 0.8f, 0.1f, 1.0f);
		//shader.set_uniform_1i("u_texture", 0);

		{
			shader->Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), *model_translatorA);
			glm::mat4 mvp = proj * view * model;
			shader->set_uniform_v4("u_mvp", mvp);
			renderer->Draw(*va, *ib, *shader);
		}


		{
			shader->Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), *model_translatorB);
			glm::mat4 mvp = proj * view * model;
			shader->set_uniform_v4("u_mvp", mvp);
			renderer->Draw(*va, *ib, *shader);
		}

		// 2.gui Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			//static float f = 0.0f;
			//static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float1", &model_translatorA->x, -100.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("float2", &model_translatorA->y, -100.0f, 100.0f);
			ImGui::SliderFloat("float3", &model_translatorB->x, -100.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("float4", &model_translatorB->y, -100.0f, 100.0f);
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//	counter++;
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}
}
