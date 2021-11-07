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
