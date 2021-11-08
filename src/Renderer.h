#pragma once
#include"GL/glew.h"
#include "GLFW/glfw3.h"
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define glCall(x) clear_error(); x; ASSERT(get_error(#x, __FILE__, __LINE__));

void clear_error();

bool get_error(const char* function, const char* file, int line);


class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Clear() const;
};
