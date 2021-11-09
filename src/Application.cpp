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


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
	std::cout << glGetString(GL_VERSION) << std::endl;


	float position[16] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
	};

	//float position[8] = {
	//	-0.5f, -0.5f,
	//	0.5f, -0.5f,
	//	0.5f, 0.5f,
	//	-0.5f, 0.5f,
	//};


	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};


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
	Texture texture("res/texture/ogl_sm.jpg");
	texture.Bind();
	shader.set_uniform_1i("u_texture", 0);


	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.5f;
	float increament = 0.01f;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		shader.Bind();
		shader.set_uniform_4f("u_Color", r, 0.8f, 0.1f, 1.0f);
		//shader.set_uniform_1i("u_texture", 0);


		glCall(renderer.Draw(va, ib, shader));

		if (r >= 1.0f)
			increament = -0.05f;
		else if (r <= 0.0f)
			increament = 0.05f;
		r += increament;
		std::cout << r << std::endl;



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	shader.Unbind();
	va.Unbind();
	ib.Unbind();
	vb.Unbind();
	glfwTerminate();
	return 0;
}
