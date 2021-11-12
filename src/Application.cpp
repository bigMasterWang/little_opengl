#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include"Texture.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"tests/TestClearColor.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1600, 900, "my son guanju, come to nanjing soon", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}





	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit())
	{
		std::cout << "ERROR!!!" << std::endl;
	}
	glfwSwapInterval(1); // Enable vsync
	std::cout << glGetString(GL_VERSION) << std::endl;



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



	VertexArray va;
	VertexBuffer vb(position, sizeof(float) * 16);

	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.SetLayout(vb, layout);


	IndexBuffer ib(indices, 6);




	Shader shader("res/shader/base.shader");
	shader.Bind();
	shader.set_uniform_4f("u_Color", 0.0f, 0.8f, 0.1f, 1.0f);


	// 对图片有很高的要求, 有的就是不行
	Texture texture("res/texture/gj.jpg");
	texture.Bind();
	shader.set_uniform_1i("u_texture", 0);


	glm::mat4 proj = glm::ortho(0.0f, 200.0f, 0.0f, 200.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::vec3 model_translatorA(0.0f, 0.0f, 0.0f);
	glm::vec3 model_translatorB(100.0f, 0.0f, 0.0f);





	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.5f;
	float increament = 0.01f;


	// gui Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();



	// gui Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	test::TestCleraColor test;
	float _color[4]{ 0.0f,0.0f,1.0f,1.0f };


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		renderer.Clear();

		//gui
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		if (r >= 1.0f)
			increament = -0.05f;
		else if (r <= 0.0f)
			increament = 0.05f;
		r += increament;


		//shader.set_uniform_4f("u_Color", r, 0.8f, 0.1f, 1.0f);
		//shader.set_uniform_1i("u_texture", 0);

		{
			shader.Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), model_translatorA);
			glm::mat4 mvp = proj * view * model;
			shader.set_uniform_v4("u_mvp", mvp);
			glCall(renderer.Draw(va, ib, shader));
		}


		{
			shader.Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), model_translatorB);
			glm::mat4 mvp = proj * view * model;
			shader.set_uniform_v4("u_mvp", mvp);
			glCall(renderer.Draw(va, ib, shader));
		}


		//why this work???
		test.OnRender();
		test.OnImGuiRender();

		// 2.gui Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			//static float f = 0.0f;
			//static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			//ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float1", &model_translatorA.x, -100.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("float2", &model_translatorA.y, -100.0f, 100.0f);
			ImGui::SliderFloat("float3", &model_translatorB.x, -100.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("float4", &model_translatorB.y, -100.0f, 100.0f);
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//	counter++;
			//ImGui::SameLine();
			//ImGui::Text("counter = %d", counter);

			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}


		//gui Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}


	//gui Cleanup
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	shader.Unbind();
	va.Unbind();
	ib.Unbind();
	vb.Unbind();
	glfwTerminate();
	return 0;
}
