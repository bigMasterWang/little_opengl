#pragma once
#include <GL\glew.h>


class VertexBuffer
{
private:
	unsigned int m_render_id;
public:
	VertexBuffer(const void* data, float size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
