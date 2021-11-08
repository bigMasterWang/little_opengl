#pragma once
#include"VertexBufferLayout.h"
#include"VertexBuffer.h"

class VertexArray
{
private:
	unsigned int m_render_id;
public:
	VertexArray();
	~VertexArray();

	void SetLayout(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};
