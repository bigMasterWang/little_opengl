#include"Renderer.h"
#include<iostream>
void clear_error()
{
	while (glGetError() != GL_NO_ERROR);
}

bool get_error(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[ GL ERROR ] (" << error << ")" << std::endl;
		std::cout << "func: " << function << std::endl;
		std::cout << "file: " << file << std::endl;
		std::cout << "line: " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
